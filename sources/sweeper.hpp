#ifndef SWEEPER_HPP
#define SWEEPER_HPP

#include <memory>
#include <string>

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

private:
  void printParams() const;

  void checkFile();
  void checkDirectory();

  string m_jsonFile;
  string m_outputDir;

  std::unique_ptr<json::value> m_jsonObjectPtr;

  bool m_isFileOk = false;
  bool m_isOutputDirOk = false;
};

#endif // SWEEPER_HPP