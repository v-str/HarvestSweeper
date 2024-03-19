#include "sweep_worker.hpp"

#include "tools.hpp"

SweepWorker::SweepWorker(const string &outputDirPath,
                         const unordered_map<string, string> &fullMap)
    : m_outputDirPath(outputDirPath), m_fullMap(fullMap) {}
