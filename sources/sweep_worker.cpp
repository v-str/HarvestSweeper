#include "sweep_worker.hpp"

#include <ranges>

#include "tools.hpp"

SweepWorker::SweepWorker(const string &outputDirPath,
                         const unordered_map<string, string> &mapChunk)
    : m_outputDirPath(outputDirPath), m_mapChunk(mapChunk) {}