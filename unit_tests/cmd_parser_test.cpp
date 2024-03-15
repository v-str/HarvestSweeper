#include "gmock/gmock.h"

#include <filesystem>

#include "cmd_parser.hpp"

using namespace testing;

class CmdParserTest : public Test {
public:
  CmdParser parser;
};

TEST_F(CmdParserTest, IsArgumentsInvalid) {
  int ac = 3;
  char *av[] = {"coverage_program", "invalid_arg1", "invalid_arg2"};

  parser.parse(3, av);

  EXPECT_EQ(parser.isInputFileNameValid(), false);
}

TEST_F(CmdParserTest, IsArgumentsInvalidCount) {
  int ac = 6;
  char *av[] = {"coverage_program", "invalid_arg1", "invalid_arg2",
                "invalid_arg3",     "invalid_arg4", "invalid_arg5"};

  parser.parse(ac, av);

  EXPECT_EQ(parser.isInputFileNameValid(), false);
}

TEST_F(CmdParserTest, isInputFileNameValid) {
  int ac = 5;
  char *av[] = {"coverage_program", "--input-file", "test_file", "--output-dir",
                "test_dir"};

  parser.parse(ac, av);

  EXPECT_EQ(parser.isInputFileNameValid(), true);
}

TEST_F(CmdParserTest, GetCmdArgsFromParser) {
  int ac = 5;
  char *av[] = {"coverage_program", "--input-file", "test_file", "--output-dir",
                "test_dir"};

  parser.parse(ac, av);

  EXPECT_EQ(parser.getInputFileName(), "test_file");
  EXPECT_EQ(parser.getOutputDirName(), "test_dir");
}

TEST_F(CmdParserTest, GetCmdArgsFromParserWithOutdirAsDot) {
  int ac = 5;
  char *av[] = {"coverage_program", "--input-file", "test.json", "--output-dir",
                "."};

  parser.parse(ac, av);

  // get current working directory
  std::filesystem::path cwd = std::filesystem::current_path();

  EXPECT_EQ(parser.getInputFileName(), "test.json");
  EXPECT_EQ(parser.getOutputDirName(), cwd.string());
}

TEST_F(CmdParserTest, OutdirWithDotAndSlash) {
  int ac = 5;
  char *av[] = {"coverage_program", "--input-file", "test.json", "--output-dir",
                "./"};

  parser.parse(ac, av);

  // get current working directory
  std::filesystem::path cwd = std::filesystem::current_path();

  EXPECT_EQ(parser.getInputFileName(), "test.json");
  EXPECT_EQ(parser.getOutputDirName(), cwd.string());
}

TEST_F(CmdParserTest, CatchBoostException) {
  int ac = 2;
  char *av[] = {"coverage_program", "--xyz"};

  parser.parse(ac, av);

  EXPECT_EQ(parser.isInputFileNameValid(), false);
}

TEST_F(CmdParserTest, NoArgumentsPassed) {
  int ac = 1;
  char *av[] = {"coverage_program"};

  parser.parse(ac, av);

  EXPECT_EQ(parser.isInputFileNameValid(), false);
}

TEST_F(CmdParserTest, InputFileNotFound) {
  int ac = 5;
  char *av[] = {"coverage_program", "--input-file", "nofile", "--output-dir",
                "test_dir"};

  parser.parse(ac, av);

  EXPECT_EQ(parser.isInputFileNameValid(), false);
}
