#include <iostream>

#include "cmd_parser.hpp"

int main(int argc, char *argv[]) {
  CmdParser cmd(argc, argv);

  if (cmd.isArgumentsValid()) {
    std::cout << cmd.getInputFileName() << std::endl;
    std::cout << cmd.getOutputDirName() << std::endl;
  }
}