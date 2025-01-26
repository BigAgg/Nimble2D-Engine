#ifndef LOGGER_H
#define LOGGER_H

#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace logger {
inline std::string getTimestamp() {
  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);

  std::ostringstream oss;
  oss << std::put_time(&tm, "%d-%m-%Y %H:%M:%S") << "\t";

  return oss.str();
}

inline void log(std::string from, std::string msg) {
  std::string outstr = "[" + from + "] " + msg + "\n";
  outstr = getTimestamp() + outstr;

  std::ofstream file("run.log", std::ios::app);

  if (file.is_open() && file.good()) {
    file << outstr;
  } else {
    std::cout << "Can't write to file\n";
  }
  file.close();
#ifdef DEBUG
  std::cout << outstr;
#endif
}

inline void deletelog() { std::remove("run.log"); }
} // namespace logger

#endif
