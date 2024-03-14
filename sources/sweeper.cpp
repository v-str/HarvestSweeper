#include "sweeper.hpp"

#include <filesystem>

#include "tools.hpp"

using namespace std;

Sweeper::Sweeper(const string &filePath, const string &outputDir)
    : m_filePath(filePath), m_outputDir(outputDir) {
      
    }

Sweeper::~Sweeper() {}

void Sweeper::sweep() {
  Logger::normal("Параметры получены");
  Logger::normal("Файл", m_filePath);
  Logger::normal("Директория для сохранения", m_outputDir);
}

bool Sweeper::isParamsValid() const { return m_isParamsValid; }

void Sweeper::checkParams() {

}
