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
  BinDepTest() : m_dep("/usr/lib/libQt5dOpenGL.so.5.15.12") {}
  ~BinDepTest(){};

  BinDep m_dep;
};

TEST_F(BinDepTest, getIsEqual) {

  vector<string> deps{"libcap.so.2", "libc.so.6"};

  ASSERT_EQ(deps.size(), m_dep.getDeps().size());
}