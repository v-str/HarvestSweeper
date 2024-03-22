#ifndef BIN_DEP_HPP
#define BIN_DEP_HPP

#include <elf.h>

#include <fstream>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class BinDep {
public:
  BinDep(const string &filename);
  ~BinDep();

  bool isElf() const;

  auto getView() const { return m_map | views::all; }

private:
  void addToMap(const string &depName);
  void parseElfFile();
  void parseElfHeader();
  void readElfHeader_StrTab();
  void readElfHeader_DynStr();
  void readElfDynInfo();

  void writeLog(const string &message);

  bool m_isElf = false;
  bool m_isDynStrFound = false;

  string m_filename;

  unordered_map<string, string> m_map;

  ifstream m_fileStream;
  Elf64_Ehdr m_elfHeader;
  Elf64_Shdr m_sectionHeader_StrTab;
  Elf64_Shdr m_sectionHeader_DynStr;
  Elf64_Shdr m_sectionHeader_DynInfo;
  Elf64_Dyn m_sectionDynEntry;
};

#endif // BIN_DEP_HPP
