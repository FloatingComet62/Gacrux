#include "knight.h"
#include <stdlib.h>

uint64_t knight_moves[64] = {
  0x20400,
  0x50800,
  0xa1100,
  0x142200,
  0x284400,
  0x508800,
  0xa01000,
  0x402000,
  0x2040004,
  0x5080008,
  0xa110011,
  0x14220022,
  0x28440044,
  0x50880088,
  0xa0100010,
  0x40200020,
  0x204000402,
  0x508000805,
  0xa1100110a,
  0x1422002214,
  0x2844004428,
  0x5088008850,
  0xa0100010a0,
  0x4020002040,
  0x20400040200,
  0x50800080500,
  0xa1100110a00,
  0x142200221400,
  0x284400442800,
  0x508800885000,
  0x20100010a000,
  0x402000204000,
  0x2040004020000,
  0x5080008050000,
  0xa1100110a0000,
  0x14220022140000,
  0x28440044280000,
  0x50880088500000,
  0xa0100010a00000,
  0x40200020400000,
  0x204000402000000,
  0x508000805000000,
  0xa1100110a000000,
  0x1422002214000000,
  0x2844004428000000,
  0x5088008850000000,
  0xa0100010a0000000,
  0x4020002040000000,
  0x400040200000000,
  0x800080500000000,
  0x1100110a00000000,
  0x2200221400000000,
  0x4400442800000000,
  0x8800885000000000,
  0x100010a000000000,
  0x2000204000000000,
  0x4020000000000,
  0x8050000000000,
  0x110a0000000000,
  0x22140000000000,
  0x44280000000000,
  0x88500000000000,
  0x10a00000000000,
  0x20400000000000
};

Moves_t MG_generateKnightMoves(uint8_t knight_square, Board_t* board) {
  uint64_t is_white = B_squareToBitboard(knight_square) & board->bitboard_data[W_N];
  uint64_t friendly_board = is_white ? B_getAllWhite(board) : B_getAllBlack(board);
  uint64_t enemy_board = is_white ? B_getAllBlack(board) : B_getAllWhite(board);
  uint64_t movement = knight_moves[knight_square] & ~friendly_board;

  uint8_t movement_size = B_noOfPieces(movement);
  uint8_t* pm_positions = malloc(movement_size);
  B_bitboardToSquares(pm_positions, 0, movement);

  Player_t player = is_white ? P_White() : P_Black();
  Moves_t moves = MG_Moves_Init();
  for (int i = 0; i < movement_size; i++) {
    uint8_t flag = NONE; // TODO
    uint64_t square_board = B_squareToBitboard(pm_positions[i]);
    if ((square_board & enemy_board) != 0) {
      flag = CAPTURE;
    }
    MG_Moves_addMove(
      &moves,
      M_init(knight_square, pm_positions[i], KNIGHT, player, flag)
    );
  }

  free(pm_positions);

  return moves;
}
