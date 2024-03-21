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
      Logger::info("found .dynstr");
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

vector<string> BinDep::getDeps() const { return m_deps; }

bool BinDep::isElf() const { return m_isElf; }

void BinDep::parseElfFile() {
  ifstream file(m_filename, std::ios::binary);

  if (!file.is_open()) {
    return;
  }

  Elf64_Ehdr Elf_Header;

  file.read(reinterpret_cast<char *>(&Elf_Header), sizeof(Elf_Header));

  if (Elf_Header.e_ident[EI_MAG0] != ELFMAG0 ||
      Elf_Header.e_ident[EI_MAG1] != ELFMAG1 ||
      Elf_Header.e_ident[EI_MAG2] != ELFMAG2 ||
      Elf_Header.e_ident[EI_MAG3] != ELFMAG3) {
    Logger::error("Not an ELF file: " + m_filename);
    return;
  }

  // ****

  // read section header str table
  Elf64_Shdr Section_H_StrTab;
  file.seekg(Elf_Header.e_shoff +
             (Elf_Header.e_shentsize * Elf_Header.e_shstrndx));
  file.read(reinterpret_cast<char *>(&Section_H_StrTab),
            sizeof(Section_H_StrTab));

  // read dyn str section header, find .dynstr section
  Elf64_Shdr Section_H_DynStr;
  file.seekg(Elf_Header.e_shoff);
  std::streampos file_OldPos;

  for (int i = 0; i < Elf_Header.e_shnum; i++) {
    file.read(reinterpret_cast<char *>(&Section_H_DynStr),
              sizeof(Section_H_DynStr));

    if (Section_H_DynStr.sh_type == SHT_STRTAB) {
      file_OldPos = file.tellg();

      file.seekg(Section_H_StrTab.sh_offset + Section_H_DynStr.sh_name);

      char rawName[10];
      rawName[8] = 0;

      file.read(rawName, 8);

      string sectionName(rawName);

      if (sectionName.compare(".dynstr") == 0) {
        Logger::info("found .dynstr!");
        break;
      } else {
        Section_H_DynStr.sh_type = SHT_NULL;
      }
    }
  }

  // read dynamic section header
  file.seekg(Elf_Header.e_shoff);
  Elf64_Shdr Section_H;
  for (auto i = 0; i < Elf_Header.e_shnum; i++) {
    file.read(reinterpret_cast<char *>(&Section_H), sizeof(Section_H));

    if (Section_H.sh_type == SHT_DYNAMIC) {
      auto oldPos = file.tellg();
      auto dynCount = Section_H.sh_size / Section_H.sh_entsize;

      file.seekg(Section_H.sh_offset);

      for (auto j = 0; j < dynCount; j++) {
        Elf64_Dyn Dyn_Section;
        file.read(reinterpret_cast<char *>(&Dyn_Section), sizeof(Dyn_Section));

        if (Dyn_Section.d_tag == DT_NULL) {
          break;
        }

        if (Dyn_Section.d_tag == DT_NEEDED) {
          auto dynpos = file.tellg();
          file.seekg(Section_H_DynStr.sh_offset + Dyn_Section.d_un.d_val);

          string libname;
          getline(file, libname, '\0');

          Logger::info("libname" + libname);
          file.seekg(dynpos);
        }
      }
      file.seekg(oldPos);
    }
  }
}

/*

Elf64_Ehdr Elf_H;
  Elf64_Shdr Section_H, shdr_shstrtab, shdr_dynstr;
  Elf64_Phdr Program_H;
  Elf64_Dyn Dyn_Section;
  long int oldpos, dynpos;
  int dyncount;
  char sname[1000];
  FILE *f = fopen(filename.c_str(), "rb");
  if (!f) {
    return;
  }
  if (fseek(f, 0, SEEK_SET) != 0) {
    fclose(f);
    return;
  }
  if (fread(&Elf_H, sizeof(Elf_H), 1, f) <= 0) {
    fclose(f);
    return;
  }
  if (memcmp(Elf_H.e_ident, ELFMAG, SELFMAG) != 0) {
    fclose(f);
    return;
  }
  if (fseek(f, Elf_H.e_shoff + (Elf_H.e_shentsize * Elf_H.e_shstrndx),
            SEEK_SET) != 0) {
    fclose(f);
    return;
  }
  if (fread(&shdr_shstrtab, sizeof(shdr_shstrtab), 1, f) <= 0) {
    fclose(f);
    return;
  }
  if (fseek(f, Elf_H.e_shoff, SEEK_SET) != 0) {
    fclose(f);
    return;
  }
  for (int i = 0; i < Elf_H.e_shnum; i++) {
    if (fread(&shdr_dynstr, sizeof(shdr_dynstr), 1, f) <= 0) {
      shdr_dynstr.sh_type = SHT_NULL;
      break;
    }
    if (shdr_dynstr.sh_type == SHT_STRTAB) {
      oldpos = ftell(f);
      sname[8] = 0;
      if (fseek(f, shdr_shstrtab.sh_offset + shdr_dynstr.sh_name, SEEK_SET) ==
          0) {
        fgets(sname, 8, f);
      }
      if (strcmp(sname, ".dynstr") == 0) {
        break;
      } else {
        shdr_dynstr.sh_type = SHT_NULL;
      }
      if (fseek(f, oldpos, SEEK_SET) != 0) {
        break;
      }
    }
  }
  if (fseek(f, Elf_H.e_shoff, SEEK_SET) == 0) {
    for (int i = 0; i < Elf_H.e_shnum; i++) {
      if (fread(&Section_H, sizeof(Section_H), 1, f) <= 0) {
        break;
      }
      if (Section_H.sh_type == SHT_DYNAMIC) {
        oldpos = ftell(f);
        dyncount = Section_H.sh_size / Section_H.sh_entsize;
        if (fseek(f, Section_H.sh_offset, SEEK_SET) == 0) {
          for (int i = 0; i < dyncount; i++) {
            if (fread(&Dyn_Section, sizeof(Dyn_Section), 1, f) <= 0 ||
                Dyn_Section.d_tag == DT_NULL) {
              break;
            }
            if (Dyn_Section.d_tag == DT_NEEDED) {
              dynpos = ftell(f);
              if (fseek(f, shdr_dynstr.sh_offset + Dyn_Section.d_un.d_val,
                        SEEK_SET) == 0) {
                sname[sizeof(sname) - 1] = 0;
                fgets(sname, sizeof(sname) - 1, f);
                printf("Section_H.sh_type is SHT_DYNAMIC, Dyn_Section.d_tag is "
                       "DT_NEEDED: "
                       "%s\n",
                       sname);
              }
              if (fseek(f, dynpos, SEEK_SET) != 0) {
                break;
              }
            }
          }
        }
        if (fseek(f, oldpos, SEEK_SET) != 0) {
          break;
        }
      }
    }
  }
  if (fseek(f, Elf_H.e_phoff, SEEK_SET) == 0) {
    for (int i = 0; i < Elf_H.e_phnum; i++) {
      if (fread(&Program_H, sizeof(Program_H), 1, f) <= 0) {
        break;
      }
      if (Program_H.p_type == PT_DYNAMIC) {
        oldpos = ftell(f);
        dyncount = Program_H.p_filesz / sizeof(Dyn_Section);
        if (fseek(f, Program_H.p_offset, SEEK_SET) == 0) {
          for (int i = 0; i < dyncount; i++) {
            if (fread(&Dyn_Section, sizeof(Dyn_Section), 1, f) <= 0 ||
                Dyn_Section.d_tag == DT_NULL) {
              break;
            }
            if (Dyn_Section.d_tag == DT_NEEDED) {
              dynpos = ftell(f);
              if (fseek(f, shdr_dynstr.sh_offset + Dyn_Section.d_un.d_val,
                        SEEK_SET) == 0) {
                sname[sizeof(sname) - 1] = 0;
                fgets(sname, sizeof(sname) - 1, f);
                printf("Program_H.p_type is PT_DYNAMIC, Dyn_Section.d_tag is "
                       "DT_NEEDED: %s\n",
                       sname);
              }
              if (fseek(f, dynpos, SEEK_SET) != 0) {
                break;
              }
            }
          }
        }
        if (fseek(f, oldpos, SEEK_SET) != 0) {
          break;
        }
      }
    }
  }
  fclose(f);

*/
