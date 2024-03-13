#include <iostream>

#include "cmd_parser.hpp"

int main(int argc, char *argv[]) {
  CmdParser cmd(argc, argv);

  if (cmd.isInputFileNameValid()) {
    std::cout << cmd.getInputFileName() << std::endl;
    std::cout << cmd.getOutputDirName() << std::endl;
  } else {
    std::cout << cmd.getDescription() << std::endl;
  }
}