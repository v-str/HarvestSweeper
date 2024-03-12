#include "cmd_parser.hpp"

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options;

CmdParser::CmdParser(int argc, const char **argv) {

  po::options_description description("Доступные опции");

  description.add_options()("help", "Показать справку")(
      "input-file", po::value<string>(), "Путь до JSON-файла с объектами")(
      "output-dir", po::value<string>(), "Путь до выходной директрии");

  po::variables_map variablesMap;
  po::store(po::parse_command_line(argc, argv, description), variablesMap);
  po::notify(variablesMap);

  if (variablesMap.count("help")) {
    m_isHelpRequested = true;
    return;
  }

  if (variablesMap.count("input-file") && variablesMap.count("output-dir")) {
    if (filesystem::exists(variablesMap["input-file"].as<string>())) {
      m_isArgumentsValid = true;
    }
  }
}
