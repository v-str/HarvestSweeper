#include <string>

#include "cmd_parser.hpp"
#include "sweeper.hpp"
#include "tools.hpp"

int main(int argc, char *argv[]) {
  CmdParser cmd;
  cmd.parse(argc, argv);

  if (cmd.isInputFileNameValid()) {
    Sweeper sweeper(cmd.getInputFileName(), cmd.getOutputDirName());

    if (sweeper.isEverythingOk()) {
      return 0;
    }

  } else {
    Logger::warning("Использование",
                    string(argv[0]) +
                        " --input-file example.json --output-dir dirname");
  }
}