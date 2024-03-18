#include <gmock/gmock.h>

#include <algorithm>
#include <unordered_map>

#include "sweeper.hpp"

using namespace std;
using namespace testing;

class SweeperTest : public Test {
public:
  SweeperTest() : sweeper("test.json", "test_dir") {}
  ~SweeperTest() = default;

  Sweeper sweeper;
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

/*
      "cp": "/usr/bin/cp",
      "ls": "/usr/bin/ls",
      "mkfs": "/usr/sbin/mkfs",
      "wget": "/usr/sbin/wget",
      "file": "/usr/bin/file",
      "more": "/usr/bin/more",
      "grep": "/usr/bin/grep",
      "cat": "/usr/bin/cat",
      "chmod": "/usr/bin/chmod",
      "chown": "/usr/bin/chown"
*/

TEST_F(SweeperTest, getMap) {
  sweeper.sweep();

  unordered_map<string, string> map{
      {"cp", "/usr/bin/cp"},       {"ls", "/usr/bin/ls"},
      {"mkfs", "/usr/sbin/mkfs"},  {"wget", "/usr/sbin/wget"},
      {"file", "/usr/bin/file"},   {"more", "/usr/bin/more"},
      {"grep", "/usr/bin/grep"},   {"cat", "/usr/bin/cat"},
      {"chmod", "/usr/bin/chmod"}, {"chown", "/usr/bin/chown"}};

  auto isMapsEqual = [](const unordered_map<string, string> &map1,
                        const unordered_map<string, string> &map2) {
    auto isSizeEq = (map1.size() == map2.size());

    if (map1.size() == map2.size()) {
      return is_permutation(map1.begin(), map1.end(), map2.begin());
    }

    return false;
  };

  ASSERT_TRUE(isMapsEqual(map, sweeper.getMap()));
}