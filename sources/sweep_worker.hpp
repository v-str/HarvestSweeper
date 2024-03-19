#ifndef SWEEP_WORKER_HPP
#define SWEEP_WORKER_HPP

#include <ranges>
#include <string>
#include <unordered_map>

using namespace std;

class SweepWorker {
public:
  SweepWorker(const string &outputDirPath,
              const unordered_map<string, string> &fullMap);
  ~SweepWorker() = default;

  auto getChunkViews() const {
    auto chunkViews =
        m_fullMap |
        ranges::views::transform([](const auto &pair) { return pair; }) |
        ranges::views::chunk(m_fullMap.size() / kThreadCount);

    return chunkViews;
  }

private:
  const string m_outputDirPath;
  const unordered_map<string, string> m_fullMap;
  const unsigned short kThreadCount = 4;
};

#endif // SWEEP_WORKER_HPP
