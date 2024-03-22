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

class SweepWorkerTest : public Test {
public:
  SweepWorkerTest() {
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
    testMap["chown"] = "/usr/bin/chown";
    testMap["fonts"] = "/etc/fonts";
  }
  ~SweepWorkerTest() = default;

  unordered_map<string, string> testMap;
};

TEST_F(SweepWorkerTest, outputPathIsNotExists) {
  testMap["error"] = "/usr/bin/error123";

  auto chunkView = testMap | views::all;

  string testDirPath = filesystem::current_path().string() + "/test_dir";
  filesystem::remove_all(testDirPath);

  SweepWorker<decltype(chunkView)> worker(testDirPath, chunkView);
  worker.run();

  ASSERT_FALSE(worker.isErrorOccured());
}

TEST_F(SweepWorkerTest, CopyTree) {
  auto chunkView = testMap | views::all;

  string testDirPath = filesystem::current_path().string() + "/test_dir";
  filesystem::remove_all(testDirPath);
  filesystem::create_directories(testDirPath);

  SweepWorker<decltype(chunkView)> worker(testDirPath, chunkView);
  worker.run();

  ASSERT_FALSE(worker.isErrorOccured());
}

TEST_F(SweepWorkerTest, skipIfExists) {
  auto chunkView = testMap | views::all;

  string testDirPath = filesystem::current_path().string() + "/test_dir";

  SweepWorker<decltype(chunkView)> worker(testDirPath, chunkView);
  worker.run();

  ASSERT_FALSE(worker.isErrorOccured());
}

TEST_F(SweepWorkerTest, fileIsNotExists) {
  testMap["error"] = "/usr/bin/error123";

  auto chunkView = testMap | views::all;

  string testDirPath = filesystem::current_path().string() + "/test_dir";

  SweepWorker<decltype(chunkView)> worker(testDirPath, chunkView);
  worker.run();

  ASSERT_TRUE(worker.isErrorOccured());
}
