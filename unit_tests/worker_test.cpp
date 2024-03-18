#include <gmock/gmock.h>

#include <string>
#include <unordered_map>

#include "sweep_worker.hpp"
#include "sweeper.hpp"

#include <iostream>

using namespace testing;
using namespace std;

TEST(SweepWorkerTest, first) {
  Sweeper sweeper("test.json", "result_dir");
  sweeper.sweep();

  SweepWorker sweeper_worker("result_dir", sweeper.getMap());

  EXPECT_EQ(1, 1);
}