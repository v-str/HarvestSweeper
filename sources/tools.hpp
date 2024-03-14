#ifndef TOOLS_H
#define TOOLS_H

#include <string>

#include <boost/json.hpp>

using namespace std;
namespace json = boost::json;

enum class LogColor { YELLOW, GREEN, BLUE, RED };

class Logger {
public:
  static void info(const string &title, const string &body = "");
  static void normal(const string &title, const string &body = "");
  static void warning(const string &title, const string &body = "");
  static void error(const string &title, const string &body = "");

private:
  static void print(LogColor clr, const string &title, const string &body);
};

class Tools {
public:
  static json::value getJsonObject(const string &filename);
};

#endif // TOOLS_H