#ifndef CMD_PARSER_HPP
#define CMD_PARSER_HPP

class CmdParser {
public:
  CmdParser(int argc, const char **argv);
  ~CmdParser();

  bool isArgumentsValid() const;

private:
  bool m_isArgumentsValid = false;
};

#endif // CMD_PARSER_HPP