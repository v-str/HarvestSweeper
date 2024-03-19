#include <gmock/gmock.h>

#include <string>
#include <unordered_map>

#include "sweep_worker.hpp"
#include "sweeper.hpp"

#include <iostream>

using namespace testing;
using namespace std;

class SweepWorkerTest : public Test {
public:
  SweepWorkerTest() : sweeper("test.json", "test_dir") { sweeper.sweep(); }
  ~SweepWorkerTest() = default;

  Sweeper sweeper;
};

TEST_F(SweepWorkerTest, first) {
  SweepWorker sweeper_worker("result_dir", sweeper.getMap());

  EXPECT_EQ(1, 1);
}