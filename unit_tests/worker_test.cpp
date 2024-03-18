#include <gmock/gmock.h>

#include <string>
#include <unordered_map>

#include "worker.hpp"

using namespace testing;
using namespace std;

class WorkerTest : public Test {
public:
  WorkerTest()
      : worker("test_dir",
               {{"key1", "value1"}, {"key2", "value2"}, {"key3", "value3"}}){};

protected:
  Worker worker;
};

TEST_F(WorkerTest, canBeCreated) { ASSERT_THAT(&worker, NotNull()); }