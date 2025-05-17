#pragma once
#include <raylib.h>

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "Then life decided to start ..."

class Life {
public:
  Life();
  ~Life();

  void Start() { isAlive = true; };

  void Stop() { isAlive = false; };

  void HandleInput();

  void Update();

  void SetPulse(float pulse) { this->pulse = pulse; };

private:
  bool isAlive;
  float pulse = 0.5f;
  float frameTime = 0.0f;

  bool Pulse();
};
