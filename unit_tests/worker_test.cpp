#include <gmock/gmock.h>

#include <filesystem>
#include <ranges>
#include <string>
#include <unordered_map>

#include "sweep_worker.hpp"
#include "sweeper.hpp"

#include <iostream>

using namespace testing;
using namespace std;

TEST(SweepWorker, CopyTree) {
  unordered_map<string, string> testMap;
  testMap["cp"] = "/usr/bin/cp";
  testMap["ls"] = "/usr/bin/ls";
  testMap["mkfs"] = "/usr/sbin/mkfs";
  testMap["wget"] = "/usr/sbin/wget";
  testMap["file"] = "/usr/bin/file";
  testMap["more"] = "/usr/bin/more";
  testMap["grep"] = "/usr/bin/grep";
  testMap["cat"] = "/usr/bin/cat";
  testMap["chmod"] = "/usr/bin/chmod";
  testMap["chown"] = "/usr/bin/chown";

  auto chunkView = testMap |
                   views::transform([](const auto &pair) { return pair; }) |
                   views::chunk(testMap.size() / 4);

  string testDirPath = filesystem::current_path().string() + "/test_dir";
  for (const auto &chunk : chunkView) {
    SweepWorker worker(testDirPath, chunk);
    worker.run();
  }

  EXPECT_EQ(1, 1);
}
