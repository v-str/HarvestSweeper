#include "sweeper.hpp"

#include <filesystem>

#include "tools.hpp"

Sweeper::Sweeper(const string &jsonFile, const string &outputDir)
    : m_jsonFile(jsonFile), m_outputDir(outputDir) {
  printParams();
  checkParams();
}

Sweeper::~Sweeper() {}

void Sweeper::sweep() {}

bool Sweeper::isParamsValid() const { return m_isParamsValid; }

void Sweeper::checkParams() {
  m_jsonObjectPtr = Tools::getJsonObject(m_jsonFile);
  if (m_jsonObjectPtr)
    m_isParamsValid = true;
}

void Sweeper::printParams() const {
  Logger::normal("Параметры получены");
  Logger::normal("Файл", m_jsonFile);
  Logger::normal("Директория для сохранения", m_outputDir);
}

void Sweeper::setParams(const string &jsonFile, const string &outputDir) {
  m_jsonFile = jsonFile;
  m_outputDir = outputDir;
}
