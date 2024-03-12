#include "cmd_parser.hpp"

#include <filesystem>
#include <format>
#include <iostream>
#include <string>
#include <vector>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

const string kDefaultOutputDirName = "final.tree";

CmdParser::CmdParser(int argc, char **argv) {

  string description_string = format(
      "Корректный вызов: {} --input-file /full/path --output-dir /full/path",
      argv[0]);

  po::options_description description(description_string);
  try {

    description.add_options()("input-file", po::value<string>(),
                              "Путь до JSON-файла с объектами")(
        "output-dir", po::value<string>(), "Путь до выходной директрии");

    if (argc == 1 || argc > 5) {
      std::cout << description_string << std::endl;
      return;
    }

    po::variables_map variablesMap;
    po::store(po::parse_command_line(argc, argv, description), variablesMap,
              true);
    po::notify(variablesMap);

    if (variablesMap.count("input-file")) {
      m_inputFileName = variablesMap["input-file"].as<string>();
      if (filesystem::exists(m_inputFileName)) {
        m_isArgumentsValid = true;
      } else {
        std::cout << "Файл " << m_inputFileName << " не найден" << std::endl;
      }
    }

    if (variablesMap.count("output-dir")) {
      m_outputDirName = variablesMap["output-dir"].as<string>();
    } else {
      m_outputDirName = kDefaultOutputDirName;
    }

  } catch (const po::error &e) {
    cout << e.what() << endl;
    cout << description_string << endl;
  }
}
