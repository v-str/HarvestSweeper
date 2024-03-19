#include <gmock/gmock.h>

#include <algorithm>
#include <boost/json.hpp>
#include <memory>
#include <ranges>
#include <string>
#include <vector>

#include <tools.hpp>

using namespace std;
using namespace testing;
namespace json = boost::json;

enum class Clr { yellow, red, green, blue };

class DISABLED_LoggerTest : public Test {
public:
  DISABLED_LoggerTest() {
    m_oldBuf = cout.rdbuf();
    cout.rdbuf(m_ss.rdbuf());
  }

  ~DISABLED_LoggerTest() { cout.rdbuf(m_oldBuf); }

  stringstream m_ss;
  streambuf *m_oldBuf;
};

string getExpectedString(Clr c, const string &title, const string &body) {
  string color;
  switch (c) {
  case Clr::yellow:
    color = "\033[1;33m";
    break;
  case Clr::red:
    color = "\033[1;31m";
    break;
  case Clr::green:
    color = "\033[1;32m";
    break;
  case Clr::blue:
    color = "\033[1;34m";
    break;
  }

  string resetCode = "\033[0m";

  return color + title + resetCode + ": " + body + "\n";
}

TEST_F(DISABLED_LoggerTest, infoTest) {
  Logger::info("Info", "This is an info message");
  string output = m_ss.str();

  EXPECT_EQ(output,
            getExpectedString(Clr::blue, "Info", "This is an info message"));
}

TEST_F(DISABLED_LoggerTest, warningTest) {
  Logger::warning("Warning", "This is a warning message");
  string output = m_ss.str();

  EXPECT_EQ(output, getExpectedString(Clr::yellow, "Warning",
                                      "This is a warning message"));
}

TEST_F(DISABLED_LoggerTest, normalTest) {
  Logger::normal("Normal", "This is a normal message");
  string output = m_ss.str();

  EXPECT_EQ(output, getExpectedString(Clr::green, "Normal",
                                      "This is a normal message"));
}

TEST_F(DISABLED_LoggerTest, errorTest) {
  Logger::error("Error", "This is a error message");
  string output = m_ss.str();

  EXPECT_EQ(output,
            getExpectedString(Clr::red, "Error", "This is a error message"));
}

class DISABLED_ToolsTest : public Test {
public:
  unique_ptr<json::value> getJsonObjectTest(const string &name) {
    return Tools::getJsonObject(name);
  }
};

TEST_F(DISABLED_ToolsTest, getJsonObject) {
  ASSERT_THAT(Tools::getJsonObject("test.json"), NotNull());
}

TEST_F(DISABLED_ToolsTest, getNullIfJsonObjectIsNotJsonObject) {
  ASSERT_THAT(Tools::getJsonObject("test.txt"), IsNull());
}

TEST_F(DISABLED_ToolsTest, getNullIfJsonObjectNotExist) {
  ASSERT_THAT(Tools::getJsonObject("not_exist.txt"), IsNull());
}

TEST_F(DISABLED_ToolsTest, getNullIfJsonObjectIfTestObjectBroken) {
  ASSERT_THAT(Tools::getJsonObject("broken.json"), IsNull());
}

TEST_F(DISABLED_ToolsTest, getNullIfEmptyFileName) {
  ASSERT_THAT(Tools::getJsonObject(""), IsNull());
}

TEST_F(DISABLED_ToolsTest, printTestJsonFile) {
  unique_ptr<json::value> jsonObjPtr = Tools::getJsonObject("test.json");

  ASSERT_THAT(jsonObjPtr, NotNull());
  ASSERT_TRUE(jsonObjPtr.get()->is_object());

  auto &rootArray = jsonObjPtr.get()->at("root").as_array();

  vector<json::value> valueVector;
  copy(rootArray.begin(), rootArray.end(), back_inserter(valueVector));

  auto range = valueVector | views::all;

  vector<string> etalonVector = {"cp",   "ls",   "mkfs", "wget",  "file",
                                 "more", "grep", "cat",  "chmod", "chown"};

  // лямбда, которая проверяет что все объекты из test.json есть в etalonVector
  auto isValueInArray = [&](const string &value) {
    return ranges::any_of(
        etalonVector.begin(), etalonVector.end(),
        [&](const string &etalon) { return etalon == value; });
  };

  for (const auto &object : range) {
    auto obj_pairs = object.as_object() | views::all;

    for (const auto &[key, value] : obj_pairs) {
      EXPECT_TRUE(isValueInArray(key));
    }
  }
}
