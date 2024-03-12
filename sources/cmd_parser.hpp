#ifndef CMD_PARSER_HPP
#define CMD_PARSER_HPP

#include <string>

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
};

#endif // CMD_PARSER_HPP