#include "raylib.h"
#include "sol/state.hpp"
#include <cassert>
#include <iostream>

int x = 0;

int main(int argc, char *argv[]) {
  InitWindow(800, 600, "Raylib CMake Example");
  // lua_State *L;
  sol::state lua;
  int y = 0;
  lua.set_function("beep", [&y] { ++y; });
  lua.script("beep()");
  assert(y == 1);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Hello, Raylib with CMake!", 190, 200, 20, LIGHTGRAY);
    EndDrawing();
  }
  CloseWindow();
  x++;
  std::cout << "Hello, World!\n";
  x++;
  return 0;
}
