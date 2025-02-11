#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <chrono>
#include <format>
#include <fstream>
#include <filesystem>

namespace logger {
inline std::string getTimestamp() {
  const auto now = std::chrono::system_clock::now();
  return std::format("{:%d-%m-%Y %H:%M:%OS}", now);
}

inline void log(std::string from, std::string msg) {
  const std::string outstr = getTimestamp() + "\t[" + from + "] " + msg + "\n";
  std::cout << outstr;
}

inline void deletelog() { std::remove("run.log"); }

inline void backuplog(bool isCrash) {
  if (std::filesystem::exists("run.log")) {
    int fileCount = 0;
    if (isCrash) {
      if (!std::filesystem::exists("./crashes/"))
        std::filesystem::create_directories("./crashes/");
      for (const auto& entry : std::filesystem::directory_iterator("./crashes/")) {
        fileCount++;
      }
      const std::string copyName = "./crashes/crash_" + std::to_string(fileCount) + ".log";
      std::filesystem::copy_file("run.log", copyName);
      return;
    }
    if (!std::filesystem::exists("./logs/"))
      std::filesystem::create_directories("./logs/");
    for (const auto& entry : std::filesystem::directory_iterator("./logs/")) {
      fileCount++;
    }
    const std::string copyName = "./logs/run_" + std::to_string(fileCount) + ".log";
    std::filesystem::copy_file("run.log", copyName);
  }
}

inline void startlogging(std::fstream &logfile, bool backup = false) {
  if (backup) {
    backuplog(false);
  }
  logfile.open("run.log", std::ios::out);
  if (!logfile.is_open() || !logfile.good())
    return;
  // Setting the std::cout buffer to be the logfile
  std::streambuf* newStreamBuffer = logfile.rdbuf();
  std::cout.rdbuf(newStreamBuffer);
  return;
}

inline void startlogging_c(FILE& logfile, bool backup = false) {
  if (backup) {
    backuplog(false);
  }
  logfile = *freopen("run.log", "w", stdout);
}
} // namespace logger

#endif
