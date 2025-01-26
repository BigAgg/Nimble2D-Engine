#include "engine.h"
#include "logger.h"
#include <cstdlib>
#include <iostream>
#include <string>

#ifndef VERSION
#define VERSION "VERSION"
#endif

int main(int argc, char *argv[]) {
  logger::deletelog();
  logger::log("NIMBLE 2D ENGINE", VERSION);
  try {
    engine::setup();
    engine::run();
    engine::saveSettings();
    engine::shutdown();
  } catch (const std::exception &e) {
    logger::log("ERROR", e.what());
    std::ifstream src("run.log", std::ios::binary);
    std::ofstream dest("crash.log", std::ios::binary);
    dest << src.rdbuf();
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
