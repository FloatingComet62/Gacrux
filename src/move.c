#include "board.h"

#include <stdio.h>

Move_t M_init(
  uint8_t initial_square,
  uint8_t final_square,
  ePiece_t piece,
  Player_t player,
  eFlag_t flag) {
  Move_t x = {
    initial_square, final_square, piece, player, flag
  };
  return x;
}

void M_print(Move_t* move) {
  printf(
    "{\n"
    "\tinitial_square: %s,\n"
    "\tfinal_square: %s,\n"
    "\tpiece: %s\n"
    "}\n",
    B_squarePrint(move->initial_square),
    B_squarePrint(move->final_square),
    PI_print(move->piece)
  );
}
