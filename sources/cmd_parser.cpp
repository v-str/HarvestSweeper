#include "cmd_parser.hpp"
#include "tools.hpp"

#include <cctype>
#include <filesystem>

namespace po = boost::program_options;

const string kDefaultTreeName = "swept.tree";
const string kJsonSuffix = ".json";

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

    checkIsInputFileNameValid();
  }
}

void CmdParser::parseOutputDirName() {
  if (m_variablesMap.count("output-dir")) {
    m_outputDirName = m_variablesMap["output-dir"].as<string>();
    if (m_outputDirName == "." || m_outputDirName == "./") {
      m_outputDirName = getCurrentPath();
    }
  } else {
    m_outputDirName = getenv("HOME");
    m_outputDirName += "/" + kDefaultTreeName;
  }
}

void CmdParser::parse(int argc, char **argv) {
  try {
    parseOptionsInternal(argc, argv);
  } catch (const po::error &e) {
    Logger::error("Сработало исключение(CmdParser::parse)", e.what());
  }
}

string CmdParser::getCurrentPath() const {
  return filesystem::current_path().string();
}

void CmdParser::checkIsInputFileNameValid() {
  if (filesystem::exists(m_inputFileName)) {

    if (m_inputFileName.find(kJsonSuffix) != string::npos) {
      if (isalpha(m_inputFileName[0])) {
        m_isInputFileNameValid = true;
      }
    }
  }
}
