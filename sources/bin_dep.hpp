#ifndef BIN_DEP_HPP
#define BIN_DEP_HPP

#include <string>
#include <vector>

using std::string, std::vector;

class BinDep {
public:
  BinDep(const string &filename);
  ~BinDep() = default;

private:
  string m_filename;
};

#endif // BIN_DEP_HPP