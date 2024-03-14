#include "sweeper.hpp"

#include "tools.hpp"

using namespace std;

Sweeper::Sweeper(const string &filePath, const string &outputDir)
    : m_filePath(filePath), m_outputDir(outputDir) {}

Sweeper::~Sweeper() {}

void Sweeper::sweep() {
  Logger::normal("Параметры получены");
  Logger::normal("\nФайл", m_filePath);
  Logger::normal("Директория для сохранения", m_outputDir);
}
