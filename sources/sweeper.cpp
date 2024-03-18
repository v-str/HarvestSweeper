#include "sweeper.hpp"

#include <filesystem>

#include "tools.hpp"

Sweeper::Sweeper(const string &jsonFile, const string &outputDir)
    : m_jsonFile(jsonFile), m_outputDir(outputDir) {
  // printParams();
  checkFile();
  checkDirectory();
}

Sweeper::~Sweeper() {}

void Sweeper::sweep() {}

void Sweeper::checkFile() {
  m_jsonObjectPtr = Tools::getJsonObject(m_jsonFile);
  if (m_jsonObjectPtr)
    m_isFileOk = true;
}

void Sweeper::printParams() const {
  Logger::normal("Файл", m_jsonFile);
  Logger::normal("Директория для сохранения", m_outputDir);
}

void Sweeper::setParams(const string &jsonFile, const string &outputDir) {
  m_jsonFile = jsonFile;
  m_outputDir = outputDir;

  checkFile();
  checkDirectory();
}

bool Sweeper::Sweeper::Sweeper::isFileOk() const { return m_isFileOk; }

bool Sweeper::Sweeper::Sweeper::isOutputDirOk() const {
  return m_isOutputDirOk;
}

void Sweeper::Sweeper::Sweeper::checkDirectory() {
  if (m_outputDir[0] != '/') {
    m_outputDir = filesystem::current_path().string() + "/" + m_outputDir;
  }

  if (filesystem::exists(m_outputDir)) {
    try {
      filesystem::remove_all(m_outputDir);
      m_isOutputDirOk = true;
    } catch (const std::exception &e) {
      Logger::error(e.what());
      m_isOutputDirOk = false;
      return;
    }
  }

  try {
    Logger::info("Создание директории ", m_outputDir);
    filesystem::create_directories(m_outputDir);
    m_isOutputDirOk = true;
  } catch (const std::exception &e) {
    Logger::error(e.what());
    m_isOutputDirOk = false;
  }
}
