#include "move_generator.h"

#include <stdlib.h>

Moves_t MG_Moves_Init() {
  Move_t* moves = malloc(16 * sizeof(Move_t));
  Moves_t x = { moves, 16, 0 };
  return x;
}
void MG_Moves_addMove(Moves_t* moves, Move_t move) {
  if (moves->moves_count == moves->buffer_size) {
    // the buffer is full, REALLOC
    moves->moves = realloc(moves->moves, moves->buffer_size + 16);
    moves->buffer_size += 16;
  }
  moves->moves[moves->moves_count] = move;
  moves->moves_count++;
}

