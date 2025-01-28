/*
*	MIT License
*
*	Copyright (c) 2025 BigAgg
*
*	Permission is hereby granted, free of charge, to any person obtaining a
copy *	of this software and associated documentation files (the "Software"), to
deal *	in the Software without restriction, including without limitation the
rights *	to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell *	copies of the Software, and to permit persons to whom the
Software is *	furnished to do so, subject to the following conditions:

*	The above copyright notice and this permission notice shall be included
in all *	copies or substantial portions of the Software.

*	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, *	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE *	SOFTWARE.
*/

#pragma once

#include "globals.h"
#include "imGuiMenus.h"
#include "imgui.h"
#include "raylib.h"
#include "rlImGui.h"
#include <algorithm>
#include <fstream>
#include <string>

namespace engine {
inline void loadDefaultSettings();
inline void loadSettings();
inline void saveSettings();
inline void setup();
inline void input();
inline void update();
inline void render();
inline void run();
inline void shutdown();
inline void HandleWindowResized();

inline void loadDefaultSettings() {
  globals::width = 1080;
  globals::height = 720;
  globals::fps = 60;
  globals::vsync = true;
  globals::fullscreen = false;
  globals::borderless = false;
  globals::maximized = true;
}

inline void loadSettings() {
  std::ifstream file("windowSettings");
  // Load Default settings if file could not be found or is corrupted
  if (!file.is_open() || !file.good()) {
    loadDefaultSettings();
    return;
  }
  // Reading file string by string
  std::string str;
  while (file >> str) {
    // Lower the read string
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    // Checking what option is loaded
    if (str == "resolution") {
      std::string tmp, val;
      file >> tmp >> val;
      tmp = "";
      for (auto &&c : val) {
        if (c == 'x') {
          globals::width = std::stoi(tmp);
          tmp = "";
          continue;
        }
        tmp += c;
      }
      globals::height = std::stoi(tmp);
    } else if (str == "fps") {
      std::string tmp, val;
      file >> tmp >> val;
      globals::fps = std::stoi(val);
    } else if (str == "vsync") {
      std::string tmp, val;
      file >> tmp >> val;
      std::transform(val.begin(), val.end(), val.begin(), ::tolower);
      if (val == "true") {
        globals::vsync = true;
      } else if (val == "false") {
        globals::vsync = false;
      } else
        globals::vsync = std::stoi(val);
    } else if (str == "fullscreen") {
      std::string tmp, val;
      file >> tmp >> val;
      std::transform(val.begin(), val.end(), val.begin(), ::tolower);
      if (val == "true")
        globals::fullscreen = true;
      else if (val == "false")
        globals::fullscreen = false;
      else
        globals::fullscreen = std::stoi(val);
    } else if (str == "borderless") {
      std::string tmp, val;
      file >> tmp >> val;
      std::transform(val.begin(), val.end(), val.begin(), ::tolower);
      if (val == "true")
        globals::borderless = true;
      else if (val == "false")
        globals::borderless = true;
      else
        globals::borderless = std::stoi(val);
    } else if (str == "maximized") {
      std::string tmp, val;
      file >> tmp >> val;
      std::transform(val.begin(), val.end(), val.begin(), ::tolower);
      if (val == "true")
        globals::maximized = true;
      else if (val == "false")
        globals::maximized = false;
      else
        globals::maximized = std::stoi(val);
    }
  }
}

inline void saveSettings() {
  std::ofstream file("windowSettings");
  if (file.is_open() && file.good()) {
    // Saving the Resolution
    file << "Resolution = " << std::to_string(globals::width) << "x"
         << std::to_string(globals::height) << "\n";
    // Saving FPS:
    file << "FPS = " << std::to_string(globals::fps) << "\n";
    // Saving vsync hint:
    file << "VSYNC = " << std::to_string(globals::vsync) << "\n";
    // Saving window states
    file << "Fullscreen = " << std::to_string(globals::fullscreen) << "\n";
    file << "Borderless = " << std::to_string(globals::borderless) << "\n";
    file << "Maximized = " << std::to_string(globals::maximized) << "\n";
  }
}

inline void loadGuiStyle() {
  ImGuiStyle &style = ImGui::GetStyle();
  std::ifstream file("imgui.style");
  if (file.is_open() && file.good()) {
    file.read((char *)&style, sizeof(ImGuiStyle));
  }
}

inline void saveGuiStyle() {
  ImGuiStyle &style = ImGui::GetStyle();
  std::ofstream file("imgui.style");
  if (file.is_open() && file.good()) {
    file.write((char *)&style, sizeof(ImGuiStyle));
  }
}

inline void setup() {
  loadSettings();
  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
  if (globals::vsync)
    SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(globals::width, globals::height, "Nimble 2D Engine");
  HandleWindowResized();
  rlImGuiSetup(true);
  loadGuiStyle();
  ImGui::LoadIniSettingsFromDisk("imgui.ini");
  globals::running = true;
}

inline void input() {
  if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_W))
    globals::running = false;
}

inline void update() { float deltatime = GetFrameTime(); }

inline void render() {
  BeginDrawing();
  ClearBackground(BLACK);
  rlImGuiBegin();

  HandleMainMenuBar();
  HandleGameSceneViewer();
  HandleObjectViewer();
  HandleAssetViewer();
  HandleComponentSelector();
  HandleFileBrowser();

  rlImGuiEnd();
  DrawFPS(GetScreenWidth() - 90, 0);
  EndDrawing();
}

inline void run() {
  while (!WindowShouldClose() && globals::running) {
    input();
    update();
    render();
    if (IsWindowResized()) {
      globals::wasResized = true;
      if (IsWindowMaximized())
        globals::maximized = true;
      if (!IsWindowMaximized()) {
        globals::width = GetScreenWidth();
        globals::height = GetScreenHeight();
        globals::maximized = false;
      }
      globals::fullscreen = false;
      globals::borderless = false;
    }
    if (globals::wasResized && IsMouseButtonUp(MOUSE_BUTTON_LEFT))
      HandleWindowResized();
  }
}

inline void shutdown() {
  ImGui::SaveIniSettingsToDisk("imgui.ini");
  saveGuiStyle();
  rlImGuiShutdown();
  CloseWindow();
}

inline void HandleWindowResized() {
  globals::wasResized = false;
  // Setting up fps
  SetTargetFPS(globals::fps);
  // Handle VSYNC hint
  if (globals::vsync)
    SetWindowState(FLAG_VSYNC_HINT);
  else
    ClearWindowState(FLAG_VSYNC_HINT);
  // Get current Monitor
  int device = GetCurrentMonitor();
  // Handle Screen modes
  if (globals::fullscreen) {
    if (IsWindowMaximized()) {
      RestoreWindow();
    }
    if (IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE)) {
      ToggleBorderlessWindowed();
    }
    SetWindowSize(GetMonitorWidth(device), GetMonitorHeight(device));
    if (!IsWindowFullscreen())
      ToggleFullscreen();
  } else if (globals::borderless) {
    if (IsWindowMaximized()) {
      RestoreWindow();
    }
    if (IsWindowFullscreen()) {
      ToggleFullscreen();
      SetWindowSize(globals::width, globals::height);
    }
    if (!IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE)) {
      SetWindowSize(GetMonitorWidth(device), GetMonitorHeight(device));
      ToggleBorderlessWindowed();
    }
  } else if (globals::maximized) {
    if (IsWindowFullscreen()) {
      ToggleFullscreen();
      SetWindowSize(globals::width, globals::height);
    }
    if (IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE)) {
      ToggleBorderlessWindowed();
      SetWindowSize(globals::width, globals::height);
    }
    if (!IsWindowMaximized()) {
      MaximizeWindow();
    }
  } else {
    if (globals::width >= GetMonitorWidth(device))
      globals::width = GetMonitorWidth(device);
    if (globals::height >= GetMonitorHeight(device))
      globals::height = GetMonitorHeight(device);
    if (globals::width < MIN_WIDTH)
      globals::width = MIN_WIDTH;
    if (globals::height < MIN_HEIGHT)
      globals::height = MIN_HEIGHT;
    if (globals::width == GetMonitorWidth(device) &&
        globals::height == GetMonitorHeight(device)) {
      globals::maximized = true;
      globals::fullscreen = false;
      globals::borderless = false;
      HandleWindowResized();
      return;
    }
    if (IsWindowMaximized())
      RestoreWindow();
    if (IsWindowFullscreen())
      ToggleFullscreen();
    if (IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE))
      ToggleBorderlessWindowed();
    SetWindowSize(globals::width, globals::height);
    SetWindowPosition(GetMonitorWidth(device) / 2 - globals::width / 2,
                      GetMonitorHeight(device) / 2 - globals::height / 2);
  }
}
} // namespace engine
