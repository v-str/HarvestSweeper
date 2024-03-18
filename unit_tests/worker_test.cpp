#include <gmock/gmock.h>

#include "worker.hpp"

using namespace testing;
using namespace std;

class WorkerTest : public Test {
public:
  Worker worker;
};

TEST_F(WorkerTest, can_be_created) { ASSERT_THAT(&worker, NotNull()); }