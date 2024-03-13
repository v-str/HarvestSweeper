#ifndef CMD_PARSER_HPP
#define CMD_PARSER_HPP

#include <string>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

using namespace std;

class CmdParser {
public:
  CmdParser() = delete;
  CmdParser(int argc, char **argv);
  ~CmdParser() = default;

  bool isInputFileNameValid() const { return m_isInputFileNameValid; };
  string getDescription() const;
  string getInputFileName() const { return m_inputFileName; };
  string getOutputDirName() const { return m_outputDirName; };

private:
  void parseOptionsInternal(int argc, char **argv);
  void parseInputFileName();
  void parseOutputDirName();

  bool m_isInputFileNameValid = false;
  string m_inputFileName;
  string m_outputDirName;

  po::options_description m_description;
  po::variables_map m_variablesMap;
};

#endif // CMD_PARSER_HPP