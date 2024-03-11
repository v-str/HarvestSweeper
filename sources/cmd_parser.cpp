#include "cmd_parser.hpp"

CmdParser::CmdParser(int argc, const char **argv) {}

CmdParser::~CmdParser() {}

bool CmdParser::isArgumentsValid() const { return m_isArgumentsValid; }
