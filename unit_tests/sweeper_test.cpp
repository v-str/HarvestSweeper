#include <gmock/gmock.h>

#include "sweeper.hpp"

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
  sweeper.setParams("test.json", "/usr/share/man");
  ASSERT_FALSE(sweeper.isOutputDirOk());
}

TEST_F(SweeperTest, everythingOk) { ASSERT_TRUE(sweeper.isEverythingOk()); }