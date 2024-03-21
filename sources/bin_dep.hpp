#ifndef BIN_DEP_HPP
#define BIN_DEP_HPP

#include <string>
#include <vector>

using std::string, std::vector;

class BinDep {
public:
  BinDep(const string &filename);
  ~BinDep() = default;

  vector<string> getDeps() const;

private:
  void parseElfFile();

  string m_filename;
  vector<string> m_deps;
};

#endif // BIN_DEP_HPP
