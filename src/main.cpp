#include "life.h"
#include "raylib.h"

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (700)

#define LIFE_WIDTH 2000
#define LIFE_HEIGHT 2000

#define WINDOW_TITLE "Then life decided to start ..."

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(10);

  Life life = Life(LIFE_WIDTH, LIFE_HEIGHT, CELL_SIZE);

  life.Start();

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(DARKGRAY);

    life.HandleInput();

    life.Update();

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
