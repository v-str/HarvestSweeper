#ifndef CMD_PARSER_HPP
#define CMD_PARSER_HPP

class CmdParser {
public:
  CmdParser(int argc, const char **argv);
  ~CmdParser();

  bool isArgumentsValid() const { return m_isArgumentsValid; };
  bool isHelpRequested() const { return m_isHelpRequested; };

private:
  bool m_isArgumentsValid = false;
  bool m_isHelpRequested = false;
};

#endif // CMD_PARSER_HPP