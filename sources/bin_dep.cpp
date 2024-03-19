#include "bin_dep.hpp"

BinDep::BinDep(const string &filename) : m_filename(filename) {}

vector<string> BinDep::getDeps() const { return m_deps; }
