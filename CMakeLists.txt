cmake_minimum_required(VERSION 3.20)
project(Nimble2D)

if (CMAKE_GENERATOR MATCHES "Visual Studio")
  if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Set default build type to Release" Force)
  endif()
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "echo")
endif()

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)
include_directories(external/imgui)
include_directories(external/rlimgui)

# Add external libraries 
add_subdirectory(external/raylib)
add_subdirectory(external/sol)

# Add source files
add_executable(Nimble2D src/main.cpp)

# Link libraries 
target_link_libraries(Nimble2D raylib)
