#include "raylib.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include "life.h"
#include "petri.h"

Petri::Petri(unsigned int rows, unsigned int cols) : rows(rows), cols(cols) {
  len = rows * cols;

  dish = new uint8_t[len];
  nextDish = new uint8_t[len];

  // Initialize the dishes to dead cells
  memset(dish, 0, len);
  memset(nextDish, 0, len);
}

void Petri::Init() {
  srand(time(0)); // Seed the random number generator
  unsigned int x, y;

  for (unsigned int i = 0; i < len; i++) {
    x = rand() % (cols - 1);
    y = rand() % (rows - 1);
    if (!IsAlive(x, y)) {
      Breed(x, y);
    }
  }
}

void Petri::Breed(unsigned int x, unsigned int y) { SetCell(x, y, false); }

void Petri::SetCell(unsigned int x, unsigned int y, bool kill) {
  int leftOffset, rightOffset, upOffset, downOffset;
  uint8_t *cell = GetCell(x, y);

  if (cell == nullptr) {
    return; // Out of bounds
  }

  // The grid is a toroidal grid, calculate the offsets
  // wrapping around the edges
  leftOffset = (x == 0) ? cols - 1 : -1;
  rightOffset = (x == cols - 1) ? -(cols - 1) : 1;
  upOffset = (y == 0) ? len - cols : -cols;
  downOffset = (y == rows - 1) ? -(len - cols) : cols;

  // Update the neighbours count
  if (kill) {
    *cell &= ~LIFE_BIT;
    *(cell + leftOffset + upOffset) -= NEIGHBOUR_BIT;    // NW
    *(cell + upOffset) -= NEIGHBOUR_BIT;                 // N
    *(cell + rightOffset + upOffset) -= NEIGHBOUR_BIT;   // NE
    *(cell + rightOffset) -= NEIGHBOUR_BIT;              // E
    *(cell + rightOffset + downOffset) -= NEIGHBOUR_BIT; // SE
    *(cell + downOffset) -= NEIGHBOUR_BIT;               // S
    *(cell + leftOffset + downOffset) -= NEIGHBOUR_BIT;  // SW
    *(cell + leftOffset) -= NEIGHBOUR_BIT;               // W
  } else {
    *cell |= LIFE_BIT;
    *(cell + leftOffset + upOffset) += NEIGHBOUR_BIT;    // NW
    *(cell + upOffset) += NEIGHBOUR_BIT;                 // N
    *(cell + rightOffset + upOffset) += NEIGHBOUR_BIT;   // NE
    *(cell + rightOffset) += NEIGHBOUR_BIT;              // E
    *(cell + rightOffset + downOffset) += NEIGHBOUR_BIT; // SE
    *(cell + downOffset) += NEIGHBOUR_BIT;               // S
    *(cell + leftOffset + downOffset) += NEIGHBOUR_BIT;  // SW
    *(cell + leftOffset) += NEIGHBOUR_BIT;               // W
    DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, GREEN);
  }
}

void Petri::Kill(unsigned int x, unsigned int y) { SetCell(x, y, true); }

void Petri::Evolve() {
  unsigned int x, y;
  uint8_t aliveNeighbours;
  uint8_t *cell;

  int deaths, births = 0;

  // Keep the current dish until the next dish is ready
  memcpy(nextDish, dish, len);

  cell = nextDish;

  // Traverse rows by rows, and skip dead cells with no alive neighbours

  for (y = 0; y < rows; y++) {
    x = 0;

    // Traverse columns until the end of the row
    while (x < cols) {
      if (cell == 0) {
        cell++;
        x++;
        continue; // Skip dead cells with no alive neighbours
      }

      // Process the cell
      aliveNeighbours = *cell >> LIFE_BIT;

      if (*cell & LIFE_BIT) {
        // Cell is alive
        if (aliveNeighbours < 2 || aliveNeighbours > 3) {
          // Cell dies of loneliness or overpopulation
          Kill(x, y);
          deaths++;
        }
      } else {
        // Cell is dead
        if (aliveNeighbours == 3) {
          // Cell becomes alive by reproduction
          Breed(x, y);
          births++;
        }
      }
      cell++;
      x++;
    }
  }
}

// Returns an array of neighbours addresses starting from the northwest corner
// and going clockwise
void Petri::GetNeighbours(uint8_t *cell, unsigned int x, unsigned int y,
                          uint8_t *neighbours) {

  unsigned int leftOffset, rightOffset, upOffset, downOffset;

  // The grid is a toroidal grid, calculate the offsets
  // wrapping around the edges
  leftOffset = (x == 0) ? cols - 1 : x - 1;
  rightOffset = (x == cols - 1) ? -(cols - 1) : 1;
  upOffset = (y == 0) ? len - cols : -cols;
  downOffset = (y == rows - 1) ? -(len - cols) : cols;

  // Get the addresses of the neighbours
  neighbours[0] = *(cell + leftOffset + upOffset);    // NW
  neighbours[1] = *(cell + upOffset);                 // N
  neighbours[2] = *(cell + rightOffset + upOffset);   // NE
  neighbours[3] = *(cell + rightOffset);              // E
  neighbours[4] = *(cell + rightOffset + downOffset); // SE
  neighbours[5] = *(cell + downOffset);               // S
  neighbours[6] = *(cell + leftOffset + downOffset);  // SW
  neighbours[7] = *(cell + leftOffset);               // W
}

uint8_t *Petri::GetCell(unsigned int x, unsigned int y) {
  if (x >= cols || y >= rows) {
    return nullptr; // Out of bounds
  }
  // Return the address of the cell in the dish
  return dish + (y * rows) + x;
}

bool Petri::IsAlive(unsigned int x, unsigned int y) {
  uint8_t *cell = GetCell(x, y);

  if (cell == nullptr) {
    return false; // Out of bounds
  }

  // Check if the cell is alive by checking the ALIVE_BIT
  return (*cell & LIFE_BIT) != 0;
}

Petri::~Petri() {
  // Free the allocated memory for the dishes
  delete[] dish;
  delete[] nextDish;
}
