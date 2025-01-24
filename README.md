# Nimble2D
Nimble2D is a part time project of mine to create a tool for myself creating my own 2D Video game!
The Project is open to use for everyone under the [MIT License](https://mit-license.org/).

## Engine
The **engine** will be light weight providing features to create 2D scenes and handle **gameobjects** inside of them.
**Gameobjects** will be handled using an own written **ECS** **(Entity Component System)** that supports [LUA](https://www.lua.org/) as scripting language with the [sol](https://github.com/ThePhD/sol2) Wrapper!

## Rendering
Rendering is provided by [Raylib](https://www.raylib.com/) while the UI I am using is [rlImGuI](https://github.com/raylib-extras/rlImGui) and [ImGuI](https://github.com/ocornut/imgui)

## Cloning the repo:
```
git clone --recurse-submodules https://github.com/your-username/your-repository.git
```

## Building the engine
### Windows:
***Requirements***:
- [CMake](https://cmake.org/)
- Any c++ Compiler that supports c++17 or higher like gcc

**Preparing the Project**
cd into the cloned repository, create a folder named *build* and cd into the *build* folder
```sh
mkdir build
cd build
cmake ..
```

**Building debug:**
cd into the build directory *Preparing the Project* and build it in debug:
```sh
cmake --build .
```
After building the Project in **debug mode** you can find the **Executable** under "build/Debug/Nimble2D.exe"

**Building release:**
cd into the build directory *Preparing the Project* and build it in release:
```sh
cmake --build . --config Release
```
After building the Project in **release mode** you can find the **Executable** under "bin/release/"

### Linux:
Linux is currently not supported but it is planned to be in the future!

## Ressources
[Raylib](https://www.raylib.com/)

[sol](https://github.com/ThePhD/sol2)

[rlImGui](https://github.com/raylib-extras/rlImGui)

[ImGuI](https://github.com/ocornut/imgui)

## License
[MIT](https://mit-license.org/)
