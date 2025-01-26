#pragma once

#include "sol/sol.hpp"
#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// Predefinitions
class SceneHandler;
class Scene;
class Script;

class Script {
public:
  void LoadScript(std::string scriptPath) {
    lua.script_file(scriptPath);
    update = lua["update"];
    setup = lua["setup"];
    hasUpdate = update.valid();
    hasSetup = setup.valid();
  }
  void Setup() {
    if (hasSetup)
      setup();
  }
  void Update(float deltatime) {
    if (hasUpdate)
      update(deltatime);
  }

private:
  sol::state lua;
  sol::function update, setup;
  bool hasUpdate, hasSetup;
};

class Component {
public:
  virtual ~Component() = default;
  virtual void Update(float deltatime) = 0;
  virtual void Render() = 0;
  // void AddScript(Script &&script) { this->script = std::move(script); }
};

// GameObject class
class GameObject {
public:
  // Add a component by unique_ptr
  void AddComponent(std::unique_ptr<Component> c) {
    components.push_back(std::move(c));
  }

  // Template helper to create and add a derived component
  template <typename T, typename... Args> T &AddComponent(Args &&...args) {
    auto component = std::make_unique<T>(std::forward<Args>(args)...);
    T &ref = *component; // Save reference to return
    components.push_back(std::move(component));
    return ref;
  }

  // Update all components
  void Update(float deltatime) {
    for (auto &component : components) {
      component->Update(deltatime);
    }
  }

  // Render all components
  void Render() {
    for (auto &component : components) {
      component->Render();
    }
  }

private:
  std::vector<std::unique_ptr<Component>> components; // Correct type
};

class Scene {
public:
  Scene(std::string name) { this->name = name; }
  static void Load(std::string filePath) {}
  static void Save() {}
  void AddGameObject(std::unique_ptr<GameObject> obj) {
    objects.push_back(std::move(obj));
  }

  std::string name;

private:
  std::string path;
  std::vector<std::unique_ptr<GameObject>> objects;
  std::vector<std::unique_ptr<Scene>> scenes;
  std::vector<std::pair<std::string, std::pair<std::string, std::string>>>
      sceneVariables;
};

class SceneHandler {
public:
  void Run() {}
  void LoadScene(std::string &name) {}
  void UnloadScene(std::string &name) {
    auto it =
        std::find_if(scenes.begin(), scenes.end(), [&name](const Scene &scene) {
          return scene.name == name;
        });
    if (it != scenes.end()) {
      currentScene = nullptr;
      scenes.erase(it);
    }
  }
  void NewScene() {
    std::string name = "Scene_" + std::to_string(scenes.size());
    std::string current_name = "";
    if (currentScene)
      current_name = currentScene->name;
    scenes.emplace_back(name);
    for (auto &&s : scenes) {
      if (s.name == current_name) {
        currentScene = &s;
      }
    }
    if (scenes.size() == 1) {
      currentScene = &scenes[0];
    }
  }

  bool AddGlobal(std::string name, int val) {
    for (auto &&var : globalInts) {
      if (var.first == name) {
        var.second = val;
        return true;
      }
    }

    for (auto &&var : globalFloats) {
      if (var.first == name) {
        return false;
      }
    }

    for (auto &&var : globalStrings) {
      if (var.first == name) {
        return false;
      }
    }
    globalInts.emplace_back(std::make_pair(name, val));
    return true;
  }

  bool AddGlobal(std::string name, float val) {
    for (auto &&var : globalInts) {
      if (var.first == name) {
        return false;
      }
    }

    for (auto &&var : globalFloats) {
      if (var.first == name) {
        var.second = val;
        return true;
      }
    }

    for (auto &&var : globalStrings) {
      if (var.first == name) {
        return false;
      }
    }
    globalFloats.emplace_back(std::make_pair(name, val));
    return true;
  }

  bool AddGlobal(std::string name, std::string val) {
    for (auto &&var : globalInts) {
      if (var.first == name) {
        return false;
      }
    }

    for (auto &&var : globalFloats) {
      if (var.first == name) {
        return false;
      }
    }

    for (auto &&var : globalStrings) {
      if (var.first == name) {
        var.second = val;
        return true;
      }
    }
    globalStrings.emplace_back(std::make_pair(name, val));
    return true;
  }

  Scene *currentScene;
  std::vector<Scene> scenes;
  std::vector<std::pair<std::string, int>> globalInts;
  std::vector<std::pair<std::string, float>> globalFloats;
  std::vector<std::pair<std::string, std::string>> globalStrings;
  std::vector<std::pair<std::string, std::unique_ptr<GameObject>>>
      globalObjects;
};
