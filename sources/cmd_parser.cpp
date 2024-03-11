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

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);

  if (vm.count("help")) {
    m_isHelpRequested = true;
  }

  if (vm.count("object_list")) {

  }

  if (vm.count("output_dir")) {
    
  }
}

CmdParser::~CmdParser() {}
