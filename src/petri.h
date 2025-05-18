#pragma once

#include <cstdint>
#define LIFE_BIT 0x01
#define NEIGHBOUR_BIT 0x02

class Petri {
public:
  Petri(unsigned int rows, unsigned int cols);
  ~Petri();

  bool IsAlive(unsigned int x, unsigned int y);
  uint8_t *GetCell(unsigned int x, unsigned int y);
  void Breed(unsigned int x, unsigned int y);
  void Evolve();
  void Init();
  void Kill(unsigned int x, unsigned int y);

private:
  unsigned int cols;
  unsigned int len;
  unsigned int rows;

  uint8_t *dish = nullptr;
  uint8_t *nextDish = nullptr;

  void GetNeighbours(uint8_t *cell, unsigned int x, unsigned int y,
                     uint8_t *neighbours);
  void SetCell(unsigned int x, unsigned int y, bool kill);
  void UpdateNeighbours(uint8_t *cell, unsigned int x, unsigned int y,
                        uint8_t *neighbours);
};
