#ifndef BIN_DEP_HPP
#define BIN_DEP_HPP

#include <elf.h>

#include <fstream>
#include <string>
#include <vector>

using namespace std;

class BinDep {
public:
  BinDep(const string &filename);
  ~BinDep() = default;

  vector<string> getDeps() const;

  bool isElf() const;

private:
  void parse();
  void parseElfFile();
  void parseElfHeader();

  void writeLog(const string &message);

  bool m_isElf = false;

  string m_filename;

  vector<string> m_deps;

  ifstream m_fileStream;
  Elf64_Ehdr m_elfHeader;
  Elf64_Shdr m_sectionHeader_StrTab;
  Elf64_Shdr m_sectionHeader_DynStr;
  Elf64_Shdr m_sectionHeader_DynInfo;
  Elf64_Dyn m_sectionDynEntry;
};

#endif // BIN_DEP_HPP
