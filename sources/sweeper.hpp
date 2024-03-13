#ifndef SWEEPER_HPP
#define SWEEPER_HPP

#include <string>

using std::string;

class Sweeper {
public:
  Sweeper(const string &filePath, const string &outputDir);
  ~Sweeper();

  void sweep();

private:
  string m_filePath;
  string m_outputDir;
};

#endif // SWEEPER_HPP