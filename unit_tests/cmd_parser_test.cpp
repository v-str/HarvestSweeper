#include "gmock/gmock.h"

#include "cmd_parser.hpp"

TEST(CmdParserTest, IsArgumentsInvalid) {
  int ac = 3;
  char *av[] = {"coverage_program", "invalid_arg1", "invalid_arg2"};

  CmdParser parser(ac, av);

  EXPECT_EQ(parser.isInputFileNameValid(), false);
}

TEST(CmdParserTest, IsArgumentsInvalidCount) {
  int ac = 6;
  char *av[] = {"coverage_program", "invalid_arg1", "invalid_arg2",
                "invalid_arg3",     "invalid_arg4", "invalid_arg5"};

  CmdParser parser(ac, av);

  EXPECT_EQ(parser.isInputFileNameValid(), false);
}

TEST(CmdParserTest, isInputFileNameValid) {
  int ac = 5;
  char *av[] = {"coverage_program", "--input-file", "test_file", "--output-dir",
                "test_dir"};

  CmdParser parser(ac, av);

  EXPECT_EQ(parser.isInputFileNameValid(), true);
}

TEST(CmdParserTest, GetCmdArgsFromParser) {
  int ac = 5;
  char *av[] = {"coverage_program", "--input-file", "test_file", "--output-dir",
                "test_dir"};

  CmdParser parser(ac, av);

  EXPECT_EQ(parser.getInputFileName(), "test_file");
  EXPECT_EQ(parser.getOutputDirName(), "test_dir/final.tree");
}

TEST(CmdParserTest, CatchBoostException) {
  int ac = 2;
  char *av[] = {"coverage_program", "--xyz"};

  CmdParser parser(ac, av);

  EXPECT_EQ(parser.isInputFileNameValid(), false);
}

TEST(CmdParserTest, NoArgumentsPassed) {
  int ac = 1;
  char *av[] = {"coverage_program"};

  CmdParser parser(ac, av);

  EXPECT_EQ(parser.isInputFileNameValid(), false);
}

TEST(CmdParserTest, InputFileNotFound) {
  int ac = 5;
  char *av[] = {"coverage_program", "--input-file", "nofile", "--output-dir",
                "test_dir"};

  CmdParser parser(ac, av);

  EXPECT_EQ(parser.isInputFileNameValid(), false);
}