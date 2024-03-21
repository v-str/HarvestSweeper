#include "bin_dep.hpp"

#include <filesystem>
#include <stdio.h>
#include <string.h>

#include "tools.hpp"

static const string kLogDir = string(getenv("HOME")) + "/bin_dep.dir";

BinDep::BinDep(const string &filename)
    : m_filename(filename), m_fileStream(filename, std::ios::binary) {

  if (m_fileStream.fail()) {
    writeLog(filename + " : " + strerror(errno));
    return;
  }

  parse();
}

BinDep::~BinDep() {
  if (m_fileStream.is_open()) {
    m_fileStream.close();
  }
}

void BinDep::parse() {
  parseElfHeader();

  if (m_isElf) {
    readElfHeader_StrTab();
    readElfHeader_DynStr();

    if (m_isDynStrFound) {
      readElfDynInfo();
    } else {
      writeLog(m_filename + " : no dynstr");
    }
  }
}

void BinDep::parseElfHeader() {
  m_fileStream.read(reinterpret_cast<char *>(&m_elfHeader),
                    sizeof(m_elfHeader));

  if (m_elfHeader.e_ident[EI_MAG0] != ELFMAG0 ||
      m_elfHeader.e_ident[EI_MAG1] != ELFMAG1 ||
      m_elfHeader.e_ident[EI_MAG2] != ELFMAG2 ||
      m_elfHeader.e_ident[EI_MAG3] != ELFMAG3) {
    writeLog(m_filename + " : " + "Not an ELF file");
  } else {
    m_isElf = true;
  }
}

void BinDep::readElfHeader_StrTab() {
  m_fileStream.seekg(m_elfHeader.e_shoff +
                     (m_elfHeader.e_shentsize * m_elfHeader.e_shstrndx));
  m_fileStream.read(reinterpret_cast<char *>(&m_sectionHeader_StrTab),
                    sizeof(m_sectionHeader_StrTab));
}

void BinDep::readElfHeader_DynStr() {
  m_fileStream.seekg(m_elfHeader.e_shoff);

  streampos filePos;

  for (auto i = 0; i < m_elfHeader.e_shnum; i++) {

    m_fileStream.read(reinterpret_cast<char *>(&m_sectionHeader_DynStr),
                      sizeof(m_sectionHeader_DynStr));

    if (m_sectionHeader_DynStr.sh_type == SHT_STRTAB) {
      filePos = m_fileStream.tellg();

      m_fileStream.seekg(m_sectionHeader_StrTab.sh_offset +
                         m_sectionHeader_DynStr.sh_name);

      char rawName[10];
      rawName[8] = 0;
      m_fileStream.read(rawName, 8);

      string sectionName(rawName);

      if (sectionName.compare(".dynstr") == 0) {
        m_isDynStrFound = true;
        break;
      } else {
        m_isDynStrFound = false;
      }
    }
  }
}

void BinDep::readElfDynInfo() {
  m_fileStream.seekg(m_elfHeader.e_shoff);

  for (auto i = 0; i < m_elfHeader.e_shnum; i++) {
    m_fileStream.read(reinterpret_cast<char *>(&m_sectionHeader_DynInfo),
                      sizeof(m_sectionHeader_DynInfo));

    if (m_sectionHeader_DynInfo.sh_type == SHT_DYNAMIC) {
      auto oldPos = m_fileStream.tellg();
      auto dynCount =
          m_sectionHeader_DynInfo.sh_size / m_sectionHeader_DynInfo.sh_entsize;

      m_fileStream.seekg(m_sectionHeader_DynInfo.sh_offset);

      for (auto j = 0; j < dynCount; j++) {

        m_fileStream.read(reinterpret_cast<char *>(&m_sectionDynEntry),
                          sizeof(m_sectionDynEntry));

        if (m_sectionDynEntry.d_tag == DT_NULL) {
          break;
        }

        if (m_sectionDynEntry.d_tag == DT_NEEDED) {

          auto dynPos = m_fileStream.tellg();

          m_fileStream.seekg(m_sectionHeader_DynStr.sh_offset +
                             m_sectionDynEntry.d_un.d_val);

          string tempName;
          getline(m_fileStream, tempName, '\0');

          m_depsVector.push_back(tempName);
          m_fileStream.seekg(dynPos);
        }
      }
      m_fileStream.seekg(oldPos);
    }
  }
}

void BinDep::writeLog(const string &message) {

  if (!std::filesystem::exists(kLogDir)) {
    std::filesystem::create_directory(kLogDir);
  }

  string shortName = m_filename;
  size_t npos = shortName.find_last_of("/\\");
  if (npos != string::npos) {
    shortName = shortName.substr(npos + 1);
  }

  string logFile = kLogDir + "/" + shortName + ".log";

  ofstream logStream(logFile, std::ios::app | std::ios::out);
  if (logStream.is_open()) {
    logStream << message << endl;
    logStream.close();
  } else {
    Logger::error("error", strerror(errno));
  }
}

vector<string> BinDep::getDeps() const { return m_depsVector; }

bool BinDep::isElf() const { return m_isElf; }
