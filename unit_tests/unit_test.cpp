#include <iostream>

#include "gmock/gmock.h"

#include "sweeper.hpp"

TEST(InitTest, InitTest) {
  Sweeper sweeper;
  EXPECT_EQ(1, 1);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
