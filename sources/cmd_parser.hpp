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

  bool isInputFileNameValid() const { return m_isInputFileValid; };
  string getInputFileName() const { return m_inputFileName; };
  string getOutputDirName() const { return m_outputDirName; };

private:
  bool m_isInputFileValid = false;
  string m_inputFileName;
  string m_outputDirName;

  po::options_description m_description;
};

#endif // CMD_PARSER_HPP