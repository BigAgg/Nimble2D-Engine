cmake_minimum_required(VERSION 3.10)
project(Project)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)

# Include directories
include_directories(include)

# Add source files

add_executable(project src/main.cpp)
