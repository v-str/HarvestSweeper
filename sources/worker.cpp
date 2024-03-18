#include "worker.hpp"

#include <ranges>

#include "tools.hpp"

Worker::Worker(const string &outputDirPath,
               const unordered_map<string, string> &mapChunk)
    : m_outputDirPath(outputDirPath), m_mapChunk(mapChunk) {

  for (const auto &[key, value] : m_mapChunk) {
    Logger::info(key, value);
  }
}
