

#include "cmd_parser.hpp"

int main(int argc, char *argv[]) {

  const char *const_argv = const_cast<const char *>(*argv);

  CmdParser cmd(argc, &const_argv);
}