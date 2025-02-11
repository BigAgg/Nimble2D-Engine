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

#ifndef VERSION
#define VERSION "0.0.0"
#endif

#include "engine.h"
#include "logger.h"
#include <cstdlib>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  // Getting starting arguments
  bool logging = false;
  if (argc > 0) {
    for (int x = 0; x < argc; x++) {
      std::string arg = argv[x];
      if (arg == "-L" || arg == "--logging")
        logging = true;
    }
  }
  // Starting main loop
  int exitCode = 0;
  try {
    engine::setup(logging);
    engine::run();
    engine::saveSettings();
  } catch (const std::exception &e) {
    logger::log("ERROR", e.what());
    exitCode = 1;
  }
  engine::shutdown();
  if (exitCode != 0)
    logger::backuplog(true);
  return exitCode;
}
