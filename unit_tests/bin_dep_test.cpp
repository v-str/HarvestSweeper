#include <gmock/gmock.h>

#include <algorithm>
#include <string>
#include <vector>

#include "bin_dep.hpp"
#include "tools.hpp"

using namespace testing;
using namespace std;

class BinDepTest : public Test {
public:
  BinDepTest() : m_dep("/usr/bin/ls") {}
  ~BinDepTest(){};

  BinDep m_dep;
};

TEST_F(BinDepTest, getIsEqual) {

  vector<string> deps{"libcap.so.2", "libc.so.6"};

  ASSERT_EQ(deps.size(), m_dep.getDeps().size());
  ASSERT_EQ("libcap.so.2", m_dep.getDeps()[0]);
  ASSERT_EQ("libc.so.6", m_dep.getDeps()[1]);
}