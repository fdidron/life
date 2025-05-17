#include "life.h"
#include "raylib.h"

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(60);

  Life life = Life();

  life.Start();
  while (!WindowShouldClose()) {
    BeginDrawing();

    life.HandleInput();

    life.Update();

    ClearBackground(RAYWHITE);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
