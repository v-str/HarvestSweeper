#ifndef SWEEP_WORKER_HPP
#define SWEEP_WORKER_HPP

#include <string>
#include <unordered_map>

using namespace std;

class SweepWorker {
public:
  SweepWorker(const string &outputDirPath,
              const unordered_map<string, string> &mapChunk);
  ~SweepWorker() = default;

private:
  const string &m_outputDirPath;
  const unordered_map<string, string> &m_mapChunk;
};

#endif // SWEEP_WORKER_HPP