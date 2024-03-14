#ifndef SWEEPER_HPP
#define SWEEPER_HPP

#include <string>

using std::string;

class Sweeper {
public:
  Sweeper(const string &filePath, const string &outputDir);
  ~Sweeper();

  void sweep();

  bool isParamsValid() const;

private:
  string m_filePath;
  string m_outputDir;

  bool m_isParamsValid = false;
};

#endif // SWEEPER_HPP