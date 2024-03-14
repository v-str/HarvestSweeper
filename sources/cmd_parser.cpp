#include "cmd_parser.hpp"

#include <filesystem>
#include <format>
#include <iostream>
#include <string>
#include <vector>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

const string kDefaultTreeName = "final.tree";
const string kInputFileOptionName = "--input-file";
const string kOutputDirOptionName = "--output-dir";

const string kDescriptionString =
    format("Корректный вызов: ./program {} \"full path to "
           "file\" {} \"full path to output dir\"",
           kInputFileOptionName, kOutputDirOptionName);

CmdParser::CmdParser() : m_description("unused") {

  m_description.add_options()("input-file", po::value<string>(),
                              "Путь до JSON-файла с объектами")(
      "output-dir", po::value<string>(), "Путь до выходной директрии");
}

void CmdParser::parseOptionsInternal(int argc, char **argv) {
  if (argc < 3) {
    return;
  }

  po::store(po::parse_command_line(argc, argv, m_description), m_variablesMap);
  po::notify(m_variablesMap);

  parseInputFileName();
  parseOutputDirName();
}

void CmdParser::parseInputFileName() {
  if (m_variablesMap.count("input-file")) {
    m_inputFileName = m_variablesMap["input-file"].as<string>();
    if (filesystem::exists(m_inputFileName)) {
      m_isInputFileNameValid = true;
    }
  }
}

void CmdParser::parseOutputDirName() {
  if (m_variablesMap.count("output-dir")) {
    m_outputDirName = m_variablesMap["output-dir"].as<string>();
    if (m_outputDirName.back() != '/') {
      m_outputDirName += '/';
    }
    m_outputDirName += kDefaultTreeName;
  } else {
    m_outputDirName = getenv("HOME");
    m_outputDirName += "/" + kDefaultTreeName;
  }
}

void CmdParser::parse(int argc, char **argv) {
  try {
    parseOptionsInternal(argc, argv);
  } catch (const po::error &e) {
    std::cerr << e.what() << std::endl;
  }
}
