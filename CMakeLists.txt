cmake_minimum_required(VERSION 3.5)
project(Nimble2D)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)
include_directories(external/sol/include)

# Add external libraries 
add_subdirectory(external/raylib)

# Add ImGui source files
add_library(ImGui STATIC
  external/imgui/imgui.cpp
  external/imgui/imgui_draw.cpp
  external/imgui/imgui_demo.cpp
  external/imgui/imgui_tables.cpp
  external/imgui/imgui_widgets.cpp
)
target_include_directories(ImGui PUBLIC
  external/imgui
  external/imgui/backends
  external/raylib/src
)

# Add rlimgui source files
add_library(rlImGui STATIC
  external/rlimgui/rlImGui.cpp
)
target_include_directories(rlImGui PUBLIC
  external/rlImGui
  external/raylib/src
)
target_link_libraries(rlImGui PRIVATE raylib ImGui)

# Add lua
add_subdirectory(include/lua)
include_directories(include/lua/src)

# Add source files
add_executable(${PROJECT_NAME} src/main.cpp)

# Set the startup project for Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# Check if we're building on Windows
if(WIN32)
    # Apply additional linker options
    if(MSVC)
      target_link_options(${PROJECT_NAME} PRIVATE $<$<CONFIG:Release>:/SUBSYSTEM:WINDOWS>)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      target_link_options(${PROJECT_NAME} PRIVATE $<$<CONFIG:Release>:-mwindows>)
    endif()
endif()

if(WIN32 AND MSVC)
  target_link_options(${PROJECT_NAME} PRIVATE $<$<CONFIG:Release>:/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup>)
endif()

# Link libraries 
target_link_libraries(${PROJECT_NAME} PRIVATE raylib rlImGui ImGui lua)

# set the source directory of resources
set(RES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/res)

# Copy the contents of the res folder to the build directory if there is one
if(EXISTS ${RES_DIR})
  message(STATUS "Resource folder fond: ${RES_DIR}")
  add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${RES_DIR} $<TARGET_FILE_DIR:Nimble2D>
    COMMENT "Copying resources to the build directory..."
  )
else()
  # Skipping copying resources
  message(WARNING "Resource folder not found: ${RES_DIR}. Skipping sesource copy.")
endif()
