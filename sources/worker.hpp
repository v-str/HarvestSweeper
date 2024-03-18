#ifndef WORKER_HPP
#define WORKER_HPP

#include <string>
#include <unordered_map>

using namespace std;

class Worker {
public:
  Worker(const string &outputDirPath,
         const unordered_map<string, string> &mapChunk);
  ~Worker() = default;

private:
  const string &m_outputDirPath;
  const unordered_map<string, string> &m_mapChunk;
};

#endif // WORKER_HPP