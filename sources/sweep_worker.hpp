#ifndef SWEEP_WORKER_HPP
#define SWEEP_WORKER_HPP

#include <ranges>
#include <string>
#include <unordered_map>

#include "tools.hpp"

using namespace std;

template <typename ChunkView> class SweepWorker {
public:
  SweepWorker(const string &outputDirPath, const ChunkView &chunkView)
      : m_outputDirPath(outputDirPath), m_chunkView(chunkView) {}
  ~SweepWorker() = default;

  void run() {
    for (const auto &[key, value] : m_chunkView) {
      Logger::info(key, value);
    }
  }

private:
  const string m_outputDirPath;
  ChunkView m_chunkView;
};

#endif // SWEEP_WORKER_HPP
