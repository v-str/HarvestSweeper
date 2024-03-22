#ifndef SWEEP_WORKER_HPP
#define SWEEP_WORKER_HPP

#include <filesystem>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

#include "bin_dep.hpp"
#include "tools.hpp"

using namespace std;

template <typename ChunkView> class SweepWorker {
public:
  SweepWorker(const string &outputDirPath, const ChunkView &chunkView)
      : m_outputDirPath(outputDirPath), m_chunkView(chunkView) {}
  ~SweepWorker() = default;

  bool isErrorOccured() const { return m_isErrorOccured; }

  void run() {
    if (!filesystem::exists(m_outputDirPath)) {
      return;
    }

    for (const auto &[key, value] : m_chunkView) {

      m_currentFile = key;
      m_currentFilePath = value;

      filesystem::path fullPath(m_outputDirPath + m_currentFilePath);
      auto directoryPath = fullPath.parent_path();

      try {
        if (filesystem::exists(fullPath)) {
          continue;
        }

        if (!filesystem::exists(directoryPath)) {
          filesystem::create_directories(directoryPath);
        }

        filesystem::copy(m_currentFilePath, fullPath);
      } catch (filesystem::filesystem_error &e) {
        Logger::error(e.what());
        m_isErrorOccured = true;
        break;
      }

      processDependencies();
    }
  }

private:
  void processDependencies() {
    if (filesystem::exists(m_currentFilePath)) {
      BinDep binDep(m_currentFilePath);

      if (binDep.isElf()) {
        auto depView = binDep.getView();

        if (ranges::distance(depView) > 0) {
          for (const auto &[key, value] : depView) {
            SweepWorker<decltype(depView)> subWorker(m_outputDirPath, depView);
            subWorker.run();
          }
        }
      }
    }
  }

  const string m_outputDirPath;
  ChunkView m_chunkView;

  string m_currentFile;
  string m_currentFilePath;

  bool m_isErrorOccured = false;
};

#endif // SWEEP_WORKER_HPP
