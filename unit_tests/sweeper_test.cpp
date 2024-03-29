#include <gmock/gmock.h>

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <iterator>
#include <ranges>
#include <unordered_map>

#include "sweeper.hpp"

using namespace std;
using namespace testing;

class SweeperTest : public Test {
public:
  SweeperTest() : sweeper("test.json", "test_dir") {
    // копия файла test.json
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
  }
  ~SweeperTest() = default;

  void recreateTestDir() {
    auto fullpath = filesystem::current_path().string() + "/" + "test_dir";
    if (filesystem::exists(fullpath)) {
      filesystem::remove_all(fullpath);
    }

    filesystem::create_directories(fullpath);
  }

  Sweeper sweeper;
  unordered_map<string, string> testMap;
};

TEST_F(SweeperTest, isJasonFileOk) { ASSERT_TRUE(sweeper.isFileOk()); }

TEST_F(SweeperTest, isOutputDirOk) { ASSERT_TRUE(sweeper.isOutputDirOk()); }

TEST_F(SweeperTest, isOutputDirBadPermissions) {
  sweeper.setParams("test.json", "/usr/bin/test_dir");
  ASSERT_FALSE(sweeper.isOutputDirOk());
}

TEST_F(SweeperTest, catchSystemOutputPathDeletionError) {
  sweeper.setParams("test.json", "/usr/share/test-test");
  ASSERT_FALSE(sweeper.isOutputDirOk());
}

TEST_F(SweeperTest, everythingOk) { ASSERT_TRUE(sweeper.isEverythingOk()); }

TEST_F(SweeperTest, getMap) {

  sweeper.sweep();

  auto isMapsEqual = [](const unordered_map<string, string> &map1,
                        const unordered_map<string, string> &map2) {
    auto isSizeEq = (map1.size() == map2.size());

    if (map1.size() == map2.size()) {
      return is_permutation(map1.begin(), map1.end(), map2.begin());
    }

    return false;
  };

  ASSERT_TRUE(isMapsEqual(testMap, sweeper.getMap()));
}
