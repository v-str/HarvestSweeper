#include "gmock/gmock.h"

#include <filesystem>

#include "cmd_parser.hpp"

using namespace testing;

class DISABLED_CmdParserTest : public Test {
public:
  CmdParser parser;
};

TEST_F(DISABLED_CmdParserTest, IsArgumentsInvalid) {
  int ac = 3;
  char *av[] = {"coverage_program", "invalid_arg1", "invalid_arg2"};

  parser.parse(3, av);

  EXPECT_EQ(parser.isInputFileNameValid(), false);
}

TEST_F(DISABLED_CmdParserTest, IsArgumentsInvalidCount) {
  int ac = 6;
  char *av[] = {"coverage_program", "invalid_arg1", "invalid_arg2",
                "invalid_arg3",     "invalid_arg4", "invalid_arg5"};

  parser.parse(ac, av);

  EXPECT_EQ(parser.isInputFileNameValid(), false);
}

TEST_F(DISABLED_CmdParserTest, isInputFileNameValid) {
  int ac = 5;
  char *av[] = {"coverage_program", "--input-file", "test.json", "--output-dir",
                "test_dir"};

  parser.parse(ac, av);

  EXPECT_EQ(parser.isInputFileNameValid(), true);
}

TEST_F(DISABLED_CmdParserTest, GetCmdArgsFromParser) {
  int ac = 5;
  char *av[] = {"coverage_program", "--input-file", "test.json", "--output-dir",
                "test_dir"};

  parser.parse(ac, av);

  EXPECT_EQ(parser.getInputFileName(), "test.json");
  EXPECT_EQ(parser.getOutputDirName(), "test_dir");
}

TEST_F(DISABLED_CmdParserTest, GetCmdArgsFromParserWithOutdirAsDot) {
  int ac = 5;
  char *av[] = {"coverage_program", "--input-file", "test.json", "--output-dir",
                "."};

  parser.parse(ac, av);

  std::filesystem::path cwd = std::filesystem::current_path();

  EXPECT_EQ(parser.getInputFileName(), "test.json");
  EXPECT_EQ(parser.getOutputDirName(), cwd.string());
}

TEST_F(DISABLED_CmdParserTest, OutdirWithDotAndSlash) {
  int ac = 5;
  char *av[] = {"coverage_program", "--input-file", "test.json", "--output-dir",
                "./"};

  parser.parse(ac, av);

  // get current working directory
  std::filesystem::path cwd = std::filesystem::current_path();

  EXPECT_EQ(parser.getInputFileName(), "test.json");
  EXPECT_EQ(parser.getOutputDirName(), cwd.string());
}

TEST_F(DISABLED_CmdParserTest, CatchBoostException) {
  int ac = 2;
  char *av[] = {"coverage_program", "--xyz"};

  parser.parse(ac, av);

  EXPECT_EQ(parser.isInputFileNameValid(), false);
}

TEST_F(DISABLED_CmdParserTest, NoArgumentsPassed) {
  int ac = 1;
  char *av[] = {"coverage_program"};

  parser.parse(ac, av);

  EXPECT_EQ(parser.isInputFileNameValid(), false);
}

TEST_F(DISABLED_CmdParserTest, InputFileNotFound) {
  int ac = 5;
  char *av[] = {"coverage_program", "--input-file", "nofile", "--output-dir",
                "test_dir"};

  parser.parse(ac, av);

  EXPECT_EQ(parser.isInputFileNameValid(), false);
}

TEST_F(DISABLED_CmdParserTest, IncorrectInputFileNameExtension) {
  int ac = 5;
  char *av[] = {"coverage_program", "--input-file", "example.txt",
                "--output-dir", "test_dir"};

  parser.parse(ac, av);

  EXPECT_EQ(parser.isInputFileNameValid(), false);
}

TEST_F(DISABLED_CmdParserTest, IncorectInputFileNameBeforeExtension) {
  int ac = 5;
  char *av[] = {"coverage_program", "--input-file", ".json", "--output-dir",
                "test_dir"};

  parser.parse(ac, av);

  EXPECT_EQ(parser.isInputFileNameValid(), false);
}

TEST_F(DISABLED_CmdParserTest, IncorrectFirstLetterFileNameBeforeExtension) {
  int ac = 5;
  char *av[] = {"coverage_program", "--input-file", "_.json", "--output-dir",
                "test_dir"};

  parser.parse(ac, av);

  EXPECT_EQ(parser.isInputFileNameValid(), false);
}

TEST_F(DISABLED_CmdParserTest, isFirstLetterFileNameIsAlpha) {
  int ac = 5;
  char *av[] = {"coverage_program", "--input-file", "A.json", "--output-dir",
                "test_dir"};

  parser.parse(ac, av);
  EXPECT_EQ(parser.isInputFileNameValid(), true);

  av[2] = "a.json";

  parser.parse(ac, av);
  EXPECT_EQ(parser.isInputFileNameValid(), true);
}
