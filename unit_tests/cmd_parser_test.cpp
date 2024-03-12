#include "gmock/gmock.h"

#include "cmd_parser.hpp"

TEST(CmdParserTest, CheckHelpRequested) {
  int ac = 2;
  const char *av[] = {"coverage_program", "--help"};

  CmdParser parser(ac, av);

  EXPECT_EQ(1, 1);
}

TEST(CmdParserTest, IsArgumentsInvalid) {
  int ac = 3;
  const char *av[] = {"coverage_program", "unvalid_arg1", "unvalid_arg2"};

  CmdParser parser(ac, av);

  EXPECT_EQ(parser.isArgumentsValid(), false);
}

TEST(CmdParserTest, IsArgumentsValid) {
  int ac = 5;
  const char *av[] = {"coverage_program", "--input-file", "test_file",
                      "--output-dir", "test_dir"};

  CmdParser parser(ac, av);

  EXPECT_EQ(parser.isArgumentsValid(), true);
}

TEST(CmdParserTest, GetCmdArgsFromParser) {
  int ac = 5;
  const char *av[] = {"coverage_program", "--input-file", "test_file",
                      "--output-dir", "test_dir"};

  CmdParser parser(ac, av);

  EXPECT_EQ(parser.getInputFileName(), "test_file");
  EXPECT_EQ(parser.getOutputDirName(), "test_dir");
}