#ifndef MOVE_GENERATOR_H
#define MOVE_GENERATOR_H

#include "board.h"

/// # Moves
/// * `moves` - A buffer which contains the actual moves
/// * `buffer-size` - The size allocated to the `moves` buffer
/// * `moves_count` - The size till which moves is actually filled with data
typedef struct {
  Move_t* moves;
  uint8_t buffer_size;
  uint8_t moves_count;
} Moves_t;

Moves_t MG_Moves_Init();

/// Add a move to Moves
void MG_Moves_addMove(Moves_t* moves, Move_t move);

#endif
