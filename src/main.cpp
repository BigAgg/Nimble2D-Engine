#include "raylib.h"
#include <iostream>

int x = 0;

int main(int argc, char *argv[]) {
  InitWindow(800, 600, "Raylib CMake Example");

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
