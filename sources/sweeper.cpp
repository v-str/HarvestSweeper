#include "sweeper.hpp"

#include <format>
#include <iostream>

using namespace std;

Sweeper::Sweeper(const string &filePath, const string &outputDir)
    : m_filePath(filePath), m_outputDir(outputDir) {}

Sweeper::~Sweeper() {}

void Sweeper::sweep() {
  cout << format("Параметры получены:\n"
                 "Файл: {}\n"
                 "Выходная директория: {}\n",
                 m_filePath, m_outputDir);
}
