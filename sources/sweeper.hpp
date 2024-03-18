#ifndef SWEEPER_HPP
#define SWEEPER_HPP

#include <memory>
#include <string>
#include <unordered_map>

#include <boost/json.hpp>

using namespace std;
namespace json = boost::json;

class Sweeper {
public:
  Sweeper(const string &jsonFile, const string &outputDir);
  ~Sweeper();

  void setParams(const string &jsonFile, const string &outputDir);

  void sweep();

  bool isFileOk() const;
  bool isOutputDirOk() const;
  bool isEverythingOk() const;

  unordered_map<string, string> getMap() const;

private:
  void checkFile();
  void checkDirectory();
  void fillMap();

  string m_jsonFile;
  string m_outputDir;

  unique_ptr<json::value> m_jsonObjectPtr;
  unordered_map<string, string> m_valueMap;

  bool m_isFileOk = false;
  bool m_isOutputDirOk = false;
};

#endif // SWEEPER_HPP