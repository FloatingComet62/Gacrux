#include "move_generator.h"
#include "notation.h"

#include <inttypes.h>
#include <stdio.h>

int main() {
  Board_t board = N_board("rnbqkbnr/ppp1p1pp/8/3pPp2/8/8/PPPP1PPP/RNBQKBNR w KQkq f6 0 3");
  // Moves_t moves = MG_generatePawnMoves(N_square("a2"), &board);

  return 0;
}
