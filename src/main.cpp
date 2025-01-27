/*
*	MIT License
*
*	Copyright (c) 2025 BigAgg
*
*	Permission is hereby granted, free of charge, to any person obtaining a copy
*	of this software and associated documentation files (the "Software"), to deal
*	in the Software without restriction, including without limitation the rights
*	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*	copies of the Software, and to permit persons to whom the Software is
*	furnished to do so, subject to the following conditions:

*	The above copyright notice and this permission notice shall be included in all
*	copies or substantial portions of the Software.

*	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*	SOFTWARE.
*/

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
