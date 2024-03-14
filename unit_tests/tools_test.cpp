#include <gmock/gmock.h>

#include <string>

#include <tools.hpp>

using namespace std;
using namespace testing;

enum class Clr { yellow, red, green, blue };

class LoggerTest : public Test {
public:
  LoggerTest() {
    m_oldBuf = cout.rdbuf();
    cout.rdbuf(m_ss.rdbuf());
  }

  ~LoggerTest() { cout.rdbuf(m_oldBuf); }

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

TEST_F(LoggerTest, infoTest) {
  Logger::info("Info", "This is an info message");
  string output = m_ss.str();

  EXPECT_EQ(output,
            getExpectedString(Clr::blue, "Info", "This is an info message"));
}

TEST_F(LoggerTest, warningTest) {
  Logger::warning("Warning", "This is a warning message");
  string output = m_ss.str();

  EXPECT_EQ(output, getExpectedString(Clr::yellow, "Warning",
                                      "This is a warning message"));
}

TEST_F(LoggerTest, normalTest) {
  Logger::normal("Normal", "This is a normal message");
  string output = m_ss.str();

  EXPECT_EQ(output, getExpectedString(Clr::green, "Normal",
                                      "This is a normal message"));
}

TEST_F(LoggerTest, errorTest) {
  Logger::error("Error", "This is a error message");
  string output = m_ss.str();

  EXPECT_EQ(output,
            getExpectedString(Clr::red, "Error", "This is a error message"));
}

TEST(ToolsTest, getJsonObject) {
  ASSERT_THAT(Tools::getJsonObject("test.json"), NotNull());
}

TEST(ToolsTest, getNullIfJsonObjectIsNotJsonObject) {
  ASSERT_THAT(Tools::getJsonObject("test.txt"), IsNull());
}

TEST(ToolsTest, getNullIfJsonObjectNotExist) {
  ASSERT_THAT(Tools::getJsonObject("not_exist.txt"), IsNull());
}

TEST(ToolsTest, getNullIfEmptyFileName) {
  ASSERT_THAT(Tools::getJsonObject(""), IsNull());
}
