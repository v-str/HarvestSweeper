#include "tools.hpp"

#include <format>
#include <iostream>

using namespace std;

constexpr string embrace(LogColor clr, const string &text) {
  string colorCode;
  switch (clr) {
  case LogColor::YELLOW:
    colorCode = "\033[1;33m";
    break;
  case LogColor::GREEN:
    colorCode = "\033[1;32m";
    break;
  case LogColor::BLUE:
    colorCode = "\033[1;34m";
    break;
  case LogColor::RED:
    colorCode = "\033[1;31m";
    break;
  }
  string resetCode = "\033[0m";

  return colorCode + text + resetCode;
}

struct ColorWrapper {
  constexpr string operator()(LogColor clr, const string &wrapped) {
    return embrace(clr, wrapped);
  }
};

void Logger::info(const string &title, const string &body) {
  Logger::print(LogColor::BLUE, title, body);
}

void Logger::normal(const string &title, const string &body) {
  Logger::print(LogColor::GREEN, title, body);
}

void Logger::warning(const string &title, const string &body) {
  Logger::print(LogColor::YELLOW, title, body);
}

void Logger::error(const string &title, const string &body) {
  Logger::print(LogColor::RED, title, body);
}

void Logger::print(LogColor clr, const string &title, const string &body) {
  cout << format("{}: {}", embrace(clr, title), body) << endl;
}