#include "gmock/gmock.h"

#include "cmd_parser.hpp"

TEST(CmdParserTest, ConstructorTest) {
  int argc = 2;
  const char *argv[] = {"object_list_path", "output_dir_name"};

  CmdParser cmd_parser(argc, argv);

  EXPECT_EQ(cmd_parser.isArgumentsValid(), true);
}