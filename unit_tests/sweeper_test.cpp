#include <gmock/gmock.h>

#include "sweeper.hpp"

using namespace testing;

class SweeperTest : public Test {
public:
  SweeperTest() : sweeper("test.json", "test_dir") {}
  ~SweeperTest() = default;

  Sweeper sweeper;
};

TEST_F(SweeperTest, isParamsValid) { ASSERT_TRUE(sweeper.isParamsValid()); }