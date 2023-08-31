#ifndef PAWN_MOVE_GENERATOR_H
#define PAWN_MOVE_GENERATOR_H
#include "../move_generator.h"

/// Generate Knight moves
/// * `knight_square` - The square at which the knight is
/// * `board` - The board from which the moves need to be generated
Moves_t MG_generateKnightMoves(uint8_t knight_square, Board_t* board);

#endif
