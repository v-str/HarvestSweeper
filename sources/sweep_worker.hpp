#ifndef SWEEP_WORKER_HPP
#define SWEEP_WORKER_HPP

#include <filesystem>
#include <ranges>
#include <string>
#include <vector>

#include "bin_dep.hpp"
#include "tools.hpp"

using namespace std;

static string spaces = "";

template <typename ChunkView> class SweepWorker {
public:
  SweepWorker(const string &outputDirPath, const ChunkView &chunkView)
      : m_outputDirPath(outputDirPath), m_chunkView(chunkView) {}
  ~SweepWorker() = default;

  void run() {
    if (!std::filesystem::exists(m_outputDirPath)) {
      return;
    }

    for (const auto &[key, value] : m_chunkView) {

      m_currentFile = key;
      m_currentFilePath = value;

      findFileDependencies();
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

    if (std::filesystem::exists(m_currentFilePath)) {
      BinDep binDep(m_currentFilePath);

      if (binDep.isElf()) {
        // Logger::info(spaces + "elf", m_currentFilePath);
        spaces.push_back(' ');
      }
    }
  }

  const string m_outputDirPath;
  ChunkView m_chunkView;

  string m_currentFile;
  string m_currentFilePath;
};

#endif // SWEEP_WORKER_HPP
