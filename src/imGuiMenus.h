#pragma once

#include "globals.h"
#include "imgui.h"
#include "raylib.h"
#include <cstring>
#include <string>

using namespace ImGui;

inline bool settings_open = false;
inline bool style_editor_open = false;
inline bool global_variables_open = false;
inline bool assign_global_key = false;
inline unsigned int assign_global_key_index = -1;

inline char buff[30];

inline float MainMenuBarOffset = 19.0f;
// Component Selector Settings
inline const ImVec2 ComponentSelectorBasePos = {0.0f, MainMenuBarOffset};
inline const ImVec2 ComponentSelectorBaseSize = {232.0f, 484.0f};
// File Browser Settings
inline const ImVec2 FileBrowserBasePos = {0.0f, 484.0f};
inline const ImVec2 FileBrowserBaseSize = {232.0f, 236.0f};
// Game Scene Viewer Settings
inline const ImVec2 GameSceneViewerBasePos = {231.0f, MainMenuBarOffset};
inline const ImVec2 GameSceneViewerBaseSize = {566.0f, 484.0f};
// Asset Viewer Settings
inline const ImVec2 AssetViewerBasePos = {231.0f, 484.0f};
inline const ImVec2 AssetViewerBaseSize = {566.0f, 236.0f};
// Object Viewer Settings
inline const ImVec2 ObjectViewerBasePos = {797.0f, MainMenuBarOffset};
inline const ImVec2 ObjectViewerBaseSize = {287.0f, 720.0f};

void HandleMainMenuBar();
void HandleGameSceneViewer();
void HandleObjectViewer();
void HandleAssetViewer();
void HandleComponentSelector();
void HandleFileBrowser();
void HandleSettingsMenu();

inline void HandleMainMenuBar() {
  BeginMainMenuBar(); // Starting the MainMenuBar
#ifdef VERSION
  Text(VERSION);
#endif

  if (BeginMenu("File")) { // Starting File menu
    if (MenuItem("Open..", "Ctrl+O")) {
    }
    if (MenuItem("New", "Ctrl+N")) {
    }
    if (MenuItem("Save", "Ctrl+S")) {
    }
    if (MenuItem("Close", "Ctrl+W")) {
      globals::running = false;
    }
    EndMenu(); // Ending the "File" menu
  }
  // Manage Settings Menu
  if (MenuItem("Settings")) {
    settings_open = !settings_open;
  }
  if (settings_open) {
    HandleSettingsMenu();
  }
  // Manage Style Editor Window
  if (MenuItem("Style Editor")) {
    style_editor_open = !style_editor_open;
  }
  if (style_editor_open) {
    Begin("Style Editor", &style_editor_open);
    ShowStyleEditor();
    if (Button("Close"))
      style_editor_open = false;
    End();
  }
  // Manage Global Variables Window
  if (MenuItem("Global Variables"))
    global_variables_open = !global_variables_open;

  if (global_variables_open) {
    SetNextWindowSize(ImVec2(400, 700));
    Begin("Global Variables", &global_variables_open,
          ImGuiWindowFlags_NoResize);
    BeginTabBar("##tabs");
    // Manage Keys (Keyboard actions)
    if (BeginTabItem("Global Keys")) {
      if (Button("New Key")) {
        globals::sceneHandler.AddGlobalKey("NEW_KEY", '0');
      }
      BeginChild("Key Name", ImVec2(GetContentRegionAvail().x * 0.8f, GetContentRegionAvail().y));
      SeparatorText("Key Name");
			for (int x = 0; x < globals::sceneHandler.globalKeys.size(); x++) {
				auto data = globals::sceneHandler.globalKeys[x].first.data();
        std::string keyIndexName = "##" + std::to_string(x);
        SetNextItemWidth(GetContentRegionAvail().x);
				InputText(keyIndexName.c_str(), data, 30);
				globals::sceneHandler.globalKeys[x].first = data;
			}
      EndChild();
      SameLine();
      BeginChild("Key", GetContentRegionAvail());
      SeparatorText("Key");
      if (BeginListBox("##Key", GetContentRegionAvail())) {
        for (int x = 0; x < globals::sceneHandler.globalKeys.size(); x++) {
          std::string keyIndexName(1, globals::sceneHandler.globalKeys[x].second);
          keyIndexName += "##" + globals::sceneHandler.globalKeys[x].first;
          if (Button(keyIndexName.c_str())) {
            assign_global_key_index = x;
            assign_global_key = true;
          }
          keyIndexName = "Keycode = " + std::to_string(globals::sceneHandler.globalKeys[x].second);
          SetItemTooltip(keyIndexName.c_str());
        }
        if (assign_global_key) {
          if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            assign_global_key = false;
            assign_global_key_index = -1;
          }
          const int newKey = GetKeyPressed();
          if (newKey != 0 && newKey < 256) {
            std::cout << newKey << "\n";
            globals::sceneHandler.globalKeys[assign_global_key_index].second = newKey;
            assign_global_key = false;
            assign_global_key_index = -1;
          }
        }
        EndListBox();
      }
      EndChild();
      EndTabItem();
    }
    // Manage Variables
    if (BeginTabItem("Global Variables")) {
      SeparatorText("Variable Name         Value");
      EndTabItem();
    }
    EndTabBar();
    if (Button("Close"))
      global_variables_open = false;
    End();
  }

  EndMainMenuBar(); // Ending the MainMenuBar
}

inline void HandleSettingsMenu() {
  Begin("Settings", &settings_open,
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_AlwaysAutoResize); // Starting Settings Window

  if (Checkbox("Fullscreen", &globals::fullscreen)) {
    if (globals::fullscreen) {
      globals::borderless = false;
      globals::maximized = false;
    }
    globals::wasResized = true;
  }
  SameLine();
  if (Checkbox("Borderless", &globals::borderless)) {
    if (globals::borderless) {
      globals::fullscreen = false;
      globals::maximized = false;
    }
    globals::wasResized = true;
  }
  SameLine();
  if (Checkbox("Maximized", &globals::maximized)) {
    if (globals::maximized) {
      globals::fullscreen = false;
      globals::borderless = false;
    }
    globals::wasResized = true;
  }
  SeparatorText("Resolution");
  if (SliderInt("Width", &globals::width, MIN_WIDTH,
                GetMonitorWidth(GetCurrentMonitor()))) {
    globals::wasResized = true;
  }
  if (SliderInt("Height", &globals::height, MIN_HEIGHT,
                GetMonitorHeight(GetCurrentMonitor()))) {
    globals::wasResized = true;
  }
  SeparatorText("Misc Settings");
  if (SliderInt("FPS", &globals::fps, 30, 320)) {
    globals::wasResized = true;
  }
  if (Checkbox("VSYNC", &globals::vsync)) {
    globals::wasResized = true;
  }
  SeparatorText("");
  if (Button("Close"))
    settings_open = false;
  End(); // Ending Settings Window
}

inline void HandleGameSceneViewer() {
  ImVec2 currentPos(GameSceneViewerBasePos.x *
                        ((float)GetScreenWidth() / MIN_WIDTH),
                    GameSceneViewerBasePos.y);
  ImVec2 currentSize(
      GameSceneViewerBaseSize.x * ((float)GetScreenWidth() / MIN_WIDTH),
      GameSceneViewerBaseSize.y * ((float)GetScreenHeight() / MIN_HEIGHT) -
          MainMenuBarOffset);
  SetNextWindowPos(currentPos);
  SetNextWindowSize(currentSize);
  Begin("Game Scene Viewer", NULL,
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_MenuBar); // Starting Game Scene Viewer

  BeginMenuBar();
  if (MenuItem("Create Scene")) {
    globals::sceneHandler.NewScene();
  }

  bool openpopuptemp = false;

  if (MenuItem("Rename Scene")) {
    if (globals::sceneHandler.currentScene) {
      openpopuptemp = true;
      globals::sceneHandler.currentScene->name.copy(buff, 30);
      buff[sizeof(buff) - 1] = 0;
    }
  }
  if (openpopuptemp) {
    OpenPopup("Rename Scene");
    openpopuptemp = false;
  }
  if (BeginPopupModal("Rename Scene", NULL,
                      ImGuiWindowFlags_AlwaysAutoResize)) {
    InputText("Scene Name", buff, 30);
    if (Button("Close")) {
      CloseCurrentPopup();
    }
    SameLine();
    if (Button("Submit")) {
      globals::sceneHandler.currentScene->name = buff;
      CloseCurrentPopup();
    }
    EndPopup();
  }

  if (Button("Close Scene")) {
    globals::sceneHandler.UnloadScene(globals::sceneHandler.currentScene->name);
  }

  EndMenuBar();

  BeginTabBar("##tabs", ImGuiTabBarFlags_FittingPolicyDefault_ |
                            ImGuiTabBarFlags_Reorderable);
  // Rendering Scene Selector
  for (auto &&s : globals::sceneHandler.scenes) {
    if (BeginTabItem(s.name.c_str())) {
      globals::sceneHandler.currentScene = &s;
      EndTabItem();
    }
  }
  EndTabBar();
  End(); // Ending Game Scene Viewer
}

inline void HandleObjectViewer() {
  ImVec2 currentPos(ObjectViewerBasePos.x *
                        ((float)GetScreenWidth() / MIN_WIDTH),
                    ObjectViewerBasePos.y);
  ImVec2 currentSize(
      ObjectViewerBaseSize.x * ((float)GetScreenWidth() / MIN_WIDTH),
      ObjectViewerBaseSize.y * ((float)GetScreenHeight() / MIN_HEIGHT) -
          MainMenuBarOffset);
  SetNextWindowPos(currentPos);
  SetNextWindowSize(currentSize);
  Begin("ObjectViewer", NULL,
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoMove); // Starting Game Scene Viewer
  End();                              // Ending Object Viewer
}

inline void HandleAssetViewer() {
  ImVec2 currentPos(
      AssetViewerBasePos.x * ((float)GetScreenWidth() / MIN_WIDTH),
      AssetViewerBasePos.y * ((float)GetScreenHeight() / MIN_HEIGHT));
  ImVec2 currentSize(
      AssetViewerBaseSize.x * ((float)GetScreenWidth() / MIN_WIDTH),
      AssetViewerBaseSize.y * ((float)GetScreenHeight() / MIN_HEIGHT));
  SetNextWindowPos(currentPos);
  SetNextWindowSize(currentSize);
  Begin("Asset Viewer", NULL,
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoMove);
  End();
}

inline void HandleComponentSelector() {
  ImVec2 currentPos(ComponentSelectorBasePos.x *
                        ((float)GetScreenWidth() / MIN_WIDTH),
                    ComponentSelectorBasePos.y);
  ImVec2 currentSize(
      ComponentSelectorBaseSize.x * ((float)GetScreenWidth() / MIN_WIDTH),
      ComponentSelectorBaseSize.y * ((float)GetScreenHeight() / MIN_HEIGHT) -
          MainMenuBarOffset);
  SetNextWindowPos(currentPos);
  SetNextWindowSize(currentSize);
  Begin("Component Selector", NULL,
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoMove | ImGuiWindowFlags_MenuBar);
  BeginMenuBar();
  EndMenuBar();
  End();
}

inline void HandleFileBrowser() {
  ImVec2 currentPos(
      FileBrowserBasePos.x * ((float)GetScreenWidth() / MIN_WIDTH),
      FileBrowserBasePos.y * ((float)GetScreenHeight() / MIN_HEIGHT));
  ImVec2 currentSize(
      FileBrowserBaseSize.x * ((float)GetScreenWidth() / MIN_WIDTH),
      FileBrowserBaseSize.y * ((float)GetScreenHeight() / MIN_HEIGHT));
  SetNextWindowPos(currentPos);
  SetNextWindowSize(currentSize);
  Begin("File Browser", NULL,
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoMove);
  End();
}
