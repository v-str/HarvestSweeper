#include "sweeper.hpp"

#include <filesystem>
#include <ranges>

#include "sweep_worker.hpp"
#include "tools.hpp"

static const unsigned short kThreadCount = 4;

Sweeper::Sweeper(const string &jsonFile, const string &outputDir)
    : m_jsonFile(jsonFile), m_outputDir(outputDir) {
  checkFile();
  checkDirectory();
}

Sweeper::~Sweeper() {}

void Sweeper::sweep() {
  // fill the map with the m_jsonFile contents
  fillMap();

  // create view chunks
  if (m_valueMap.size() > 0) {
    auto chunksViews =
        m_valueMap |
        ranges::views::transform([](const auto &pair) { return pair; }) |
        ranges::views::chunk(m_valueMap.size() / kThreadCount);

    for (const auto &chunk : chunksViews) {
      SweepWorker<decltype(chunk)> worker(m_outputDir, chunk);
    }
  }
}

void Sweeper::checkFile() {
  m_jsonObjectPtr = Tools::getJsonObject(m_jsonFile);
  if (m_jsonObjectPtr)
    m_isFileOk = true;
  else
    Logger::error("Sweeper::checkFile", "m_jsonObjectPtr is null");
}

void Sweeper::setParams(const string &jsonFile, const string &outputDir) {
  m_jsonFile = jsonFile;
  m_outputDir = outputDir;

  checkFile();
  checkDirectory();
}

bool Sweeper::Sweeper::Sweeper::isFileOk() const { return m_isFileOk; }

bool Sweeper::Sweeper::Sweeper::isOutputDirOk() const {
  return m_isOutputDirOk;
}

void Sweeper::Sweeper::Sweeper::checkDirectory() {
  if (m_outputDir[0] != '/') {
    m_outputDir = filesystem::current_path().string() + "/" + m_outputDir;
  }

  if (filesystem::exists(m_outputDir)) {
    try {
      filesystem::remove_all(m_outputDir);
      m_isOutputDirOk = true;
    } catch (const std::exception &e) {
      Logger::error(e.what());
      m_isOutputDirOk = false;
      return;
    }
  }

  try {
    Logger::info("Создание директории ", m_outputDir);
    filesystem::create_directories(m_outputDir);
    m_isOutputDirOk = true;
  } catch (const std::exception &e) {
    Logger::error(e.what());
    m_isOutputDirOk = false;
  }
}

bool Sweeper::isEverythingOk() const { return m_isFileOk && m_isOutputDirOk; }

void Sweeper::fillMap() {
  auto jsonObjectPtr = Tools::getJsonObject(m_jsonFile);

  if (jsonObjectPtr.get()->is_object()) {
    auto &rootArray = jsonObjectPtr.get()->at("root").as_array();

    for (const auto &item : rootArray.at(0).as_object()) {
      auto key = string(item.key().data(), item.key().length());
      auto jstring = item.value().as_string();
      auto value = string(jstring.c_str());

      m_valueMap[key] = value;
    }
  }
}

unordered_map<string, string> Sweeper::getMap() const { return m_valueMap; }

string Sweeper::getOutputDir() const { return m_outputDir; }
