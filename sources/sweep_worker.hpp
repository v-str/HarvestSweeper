#ifndef SWEEP_WORKER_HPP
#define SWEEP_WORKER_HPP

#include <filesystem>
#include <ranges>
#include <string>
#include <vector>

#include "tools.hpp"

using namespace std;

template <typename ChunkView> class SweepWorker {
public:
  SweepWorker(const string &outputDirPath, const ChunkView &chunkView)
      : m_outputDirPath(outputDirPath), m_chunkView(chunkView) {}
  ~SweepWorker() = default;

  void run() {
    if (!std::filesystem::exists(m_outputDirPath)) {
      Logger::error("Ошибка", m_outputDirPath + " не существует");
      return;
    }

    for (const auto &[key, value] : m_chunkView) {
      Logger::info(key, value);
      m_currentFile = key;
      m_currentFilePath = value;
    }
  }

private:
  void findFileDependencies() {
    /*
    если файл m_currentFile существует в начальном каталоге
      если файла не существует в конечном каталоге
        узнать тип файла, бинарный или нет
          если бинарный, то
            найти зависимости этого файла и записать их в вектор



    */
  }

  const string m_outputDirPath;
  ChunkView m_chunkView;

  string m_currentFile;
  string m_currentFilePath;
};

#endif // SWEEP_WORKER_HPP
