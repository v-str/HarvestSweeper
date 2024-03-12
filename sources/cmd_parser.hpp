#ifndef CMD_PARSER_HPP
#define CMD_PARSER_HPP

class CmdParser {
public:
  CmdParser() = delete;
  CmdParser(int argc, const char **argv);
  ~CmdParser() = default;

  bool isArgumentsValid() const { return m_isArgumentsValid; };

private:
  bool m_isArgumentsValid = false;
};

#endif // CMD_PARSER_HPP