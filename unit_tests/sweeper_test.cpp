#include <gmock/gmock.h>

#include "sweeper.hpp"

using namespace testing;

class SweeperTest : public Test {
public:
  SweeperTest() : sweeper("test_file", "test_dir") {}
  ~SweeperTest() = default;

  Sweeper sweeper;
};

TEST_F(SweeperTest, isParamsValid) {
  ASSERT_THAT(sweeper.isParamsValid(), Eq(true));
}