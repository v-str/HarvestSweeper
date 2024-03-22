#include <gmock/gmock.h>

#include <algorithm>
#include <iostream>
#include <ranges>
#include <string>
#include <unordered_map>

#include "bin_dep.hpp"
#include "tools.hpp"

using namespace testing;
using namespace std;

TEST(BinDepTest, isElfExist) {
  BinDep m_dep("/usr/bin/ls-ghost");

  ASSERT_TRUE(m_dep.isElf() == false);
}

TEST(BidDepTest, mapIsEqual) {
  BinDep m_dep("/usr/bin/ls");

  unordered_map<string, string> depViewTest{
      {"libc.so.6", "/usr/lib/libc.so.6"},
      {"libcap.so.2", "/usr/lib/libcap.so.2"},
  };

  auto depView = m_dep.getView();

  auto isPermutation = is_permutation(
      depView.begin(), depView.end(), depViewTest.begin(), depViewTest.end(),
      [](const auto &lhs, const auto &rhs) {
        return lhs.first == rhs.first && lhs.second == rhs.second;
      });

  ASSERT_EQ(isPermutation, true);
}
