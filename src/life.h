#pragma once
#include <cstdint>
#include <raylib.h>

#include "petri.h"

#define CELL_SIZE 5

class Life {
public:
  Life(unsigned int cols, unsigned int rows, uint16_t cellSize);

  ~Life();

  void Start() { isAlive = true; };

  void Stop() { isAlive = false; };

  void HandleInput();

  void Update();

  void SetPulse(float pulse) { this->pulse = pulse; };

private:
  // The current state of the simulation, allows for pausing
  bool isAlive;

  // The time between each pulse to choose the speed of the simulation
  float pulse = 0.5f;
  float frameTime = 0.0f;

  // Contains the current state of the cells
  Petri dish;
  uint16_t cellSize;
  // Needs to be updated every pulse, every update loop when the game isn't
  // paused
  bool Pulse();
};
