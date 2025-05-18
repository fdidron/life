#include <cstdint>
#include <raylib.h>

#include "life.h"

Life::Life(unsigned int cols, unsigned int rows, uint16_t cellSize)
    : dish(rows, cols), cellSize(cellSize) {
  // Initialize the dish with random cells
  dish.Init();
};

void Life::HandleInput() {
  if (IsKeyPressed(KEY_SPACE)) {
    if (isAlive) {
      Stop();
    } else {
      Start();
    }
  }
}

void Life::Update() {
  if (isAlive) {
    dish.Evolve();
    // Update the life state every pulse
    if (Pulse()) {
      // Evolve the dish
    }
  }
}

bool Life::Pulse() {
  frameTime += GetFrameTime();

  if (frameTime >= pulse) {
    frameTime = 0.0f;
    return true;
  }
  return false;
}

Life::~Life() {
  // Cleanup if necessary
}
