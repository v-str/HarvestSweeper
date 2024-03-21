#include <gmock/gmock.h>

#include <algorithm>
#include <ranges>
#include <string>
#include <vector>

#include "bin_dep.hpp"
#include "tools.hpp"

using namespace testing;
using namespace std;

TEST(BinDepTest, getIsEqual) {
  BinDep m_dep("/usr/bin/ls");

  vector<string> deps{"libcap.so.2", "libc.so.6"};

  ASSERT_EQ(deps.size(), m_dep.getDeps().size());
  ASSERT_EQ("libcap.so.2", m_dep.getDeps()[0]);
  ASSERT_EQ("libc.so.6", m_dep.getDeps()[1]);
}

TEST(BinDepTest, isElfExist) {
  BinDep m_dep("/usr/bin/ls-ghost");

  ASSERT_TRUE(m_dep.isElf() == false);
}

TEST(BidDepTest, getView) {
  BinDep m_dep("/usr/bin/wget");

  auto depView = m_dep.getView();

  vector<string> testDeps = {
      "libpcre2-8.so.0", "libuuid.so.1", "libidn2.so.0", "libidn2.so.0",
      "libgnutls.so.30", "libz.so.1",    "libpsl.so.5",  "libc.so.6"};

  bool isAllinView = ranges::all_of(testDeps.begin(), testDeps.end(),
                                    [&](const string &testValue) {
                                      bool isEq = false;
                                      for (const auto &depValue : depView) {
                                        if (*depValue == testValue) {
                                          isEq = true;
                                          break;
                                        }
                                      }
                                      return isEq;
                                    });

  ASSERT_EQ(isAllinView, true);
}
