#include <gmock/gmock.h>

#include <ranges>
#include <string>
#include <unordered_map>

#include "sweep_worker.hpp"
#include "sweeper.hpp"

#include <iostream>

using namespace testing;
using namespace std;

static const unsigned short kThreadCount = 4;

class SweepWorkerTest : public Test {
public:
  SweepWorkerTest() : sweeper("test.json", "test_dir") { sweeper.sweep(); }
  ~SweepWorkerTest() = default;

  Sweeper sweeper;
};

TEST_F(SweepWorkerTest, getChunkDistance) {
  SweepWorker sweeper_worker("result_dir", sweeper.getMap());

  auto chunkViews = sweeper_worker.getChunkViews();

  EXPECT_EQ(ranges::distance(chunkViews), 5);
}
