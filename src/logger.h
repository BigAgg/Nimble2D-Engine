#ifndef LOGGER_H
#define LOGGER_H

#ifdef DEBUG
  #include <iostream>
#endif

#include <string>
#include <chrono>
#include <format>

namespace logger {
inline std::string getTimestamp() {
  const auto now = std::chrono::system_clock::now();
  return std::format("{:%d-%m-%Y %H:%M:%OS}", now);
}

inline void log(std::string from, std::string msg) {
  std::string outstr = "\t[" + from + "] " + msg + "\n";
  outstr = getTimestamp() + outstr;

  std::ofstream file("run.log", std::ios::app);

  if (file.is_open() && file.good()) {
    file << outstr;
  } else {
#ifdef DEBUG
    std::cout << "Can't write to file\n";
#endif
  }
  file.close();
#ifdef DEBUG
  std::cout << outstr;
#endif
}

inline void deletelog() { std::remove("run.log"); }
} // namespace logger

#endif
