cmake_minimum_required(VERSION 3.20)
project(Nimble2D)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)
include_directories(external/imgui)
include_directories(external/rlimgui)
include_directories(external/sol/include)

# Add external libraries 
add_subdirectory(external/raylib)

# Add lua
add_subdirectory(include/lua)
include_directories(include/lua/src)

# Add source files
add_executable(Nimble2D src/main.cpp)

# Link libraries 
target_link_libraries(Nimble2D raylib lua)
