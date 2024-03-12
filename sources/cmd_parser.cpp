#include "cmd_parser.hpp"

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

CmdParser::CmdParser(int argc, const char **argv) {

  po::options_description description("Доступные опции");

  description.add_options()("help", "Показать справку")(
      "input-file", po::value<string>(), "Путь до JSON-файла с объектами")(
      "output-dir", po::value<string>(), "Путь до выходной директрии");

  po::variables_map variablesMap;
  po::store(po::parse_command_line(argc, argv, description), variablesMap,
            true);
  po::notify(variablesMap);

  if (variablesMap.count("help")) {
    cout << description << endl;
    return;
  }

  if (variablesMap.count("input-file") && variablesMap.count("output-dir")) {
    m_inputFileName = variablesMap["input-file"].as<string>();
    m_outputDirName = variablesMap["output-dir"].as<string>();
    if (filesystem::exists(m_inputFileName)) {
      m_isArgumentsValid = true;
    }
  }
}
