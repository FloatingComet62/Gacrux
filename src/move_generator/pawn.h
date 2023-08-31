#ifndef PAWN_MOVE_GENERATOR_H
#define PAWN_MOVE_GENERATOR_H
#include "../move_generator.h"

/// Generate Pawn moves
/// * `pawn_square` - The square at which the pawn is
/// * `board` - The board from which the moves need to be generated
Moves_t MG_generatePawnMoves(uint8_t pawn_square, Board_t* board);

#endif
