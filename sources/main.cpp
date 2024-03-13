#include <iostream>

#include "cmd_parser.hpp"
#include "sweeper.hpp"

int main(int argc, char *argv[]) {
  CmdParser cmd;
  cmd.parse(argc, argv);

  if (cmd.isInputFileNameValid()) {
    Sweeper sweeper(cmd.getInputFileName(), cmd.getOutputDirName());
    sweeper.sweep();
  } else {
    std::cout << cmd.getDescription() << std::endl;
  }
}