#include <iostream>
#include <raylib.h>

#include "life.h"

Life::Life() : isAlive(false) {}

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
    // Update the life state every pulse
    if (Pulse()) {
        std::cout << "Pulse!" << std::endl;
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
