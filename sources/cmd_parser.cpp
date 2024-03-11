#include "cmd_parser.hpp"

#include <filesystem>
#include <iostream>
#include <string>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

CmdParser::CmdParser(int argc, const char **argv) {
  po::options_description desc("Доступные опции");

  desc.add_options()("help,h", "Показать справку")(
      "object_list", po::value<std::string>(), "JSON-файл с объектами")(
      "output_dir", po::value<std::string>(), "Куда сохранить результат");
}

CmdParser::~CmdParser() {}

bool CmdParser::isArgumentsValid() const { return m_isArgumentsValid; }
