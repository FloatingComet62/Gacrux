#include "pawn.h"
#include <stdlib.h>

uint64_t white_pawn_moves[16] = {
  // Rank 2
  0x0000000001010000,
  0x0000000002020000,
  0x0000000004040000,
  0x0000000008080000,
  0x0000000101000000,
  0x0000000202000000,
  0x0000000404000000,
  0x0000000808000000,

  // Rank 3 - 7
  // rank_offset = B_getRank(pawn_square) - 3
  // Formula: pawn_moves[B_getFile(pawn_square) + 7] << (rank_offset * 16)
  0x0000000001000000,
  0x0000000002000000,
  0x0000000004000000,
  0x0000000008000000,
  0x0000000010000000,
  0x0000000020000000,
  0x0000000040000000,
  0x0000000080000000,
};

uint64_t black_pawn_moves[16] = {
  // Rank 7
  0x0000010100000000,
  0x0000020200000000,
  0x0000040400000000,
  0x0000080800000000,
  0x0000101000000000,
  0x0000202000000000,
  0x0000404000000000,
  0x0000808000000000,

  // Rank 6 - 2
  // rank_offset = B_getRank(pawn_square) - 3
  // Formula: pawn_moves[B_getFile(pawn_square) + 7] << (rank_offset * 16)
  0x0000000100000000,
  0x0000000200000000,
  0x0000000400000000,
  0x0000000800000000,
  0x0000001000000000,
  0x0000002000000000,
  0x0000004000000000,
  0x0000008000000000,
};
uint64_t pawn_attack_moves[8] = {
  0x0000000000000002, // A
  0x0000000000000005, // B
  0x000000000000000A, // C
  0x0000000000000014, // D
  0x0000000000000028, // E
  0x0000000000000050, // F
  0x00000000000000A0, // G
  0x0000000000000040, // H
};
uint64_t passanting_pawns[16] = {
  0x000000002000000, // a3
  0x000000005000000, // b3
  0x00000000A000000, // c3
  0x000000014000000, // d3
  0x000000028000000, // e3
  0x000000050000000, // f3
  0x0000000A0000000, // g3
  0x000000040000000, // h3
};

// imagine we have this slice of board
// 1 0 1 1 0 0 1 0 <- rank Y (3)
// 0 0 0 0 0 1 0 0
// 0 0 1 0 1 0 1 1 <- rank X (1)
//
// Expected output:
// 1 0 1 1 1 0 1 1 <- rank Y (3) = rank Y | rank X
// 0 0 0 0 0 1 0 0
// 0 0 1 0 1 0 1 1
uint64_t maskRankXToRankY(uint8_t x, uint8_t y, uint64_t board) {
  uint8_t rankX = (board >> ((x - 1) * 8)) & 0b11111111;
  board |= rankX << ((y - 1) * 8);
  return board;
}

Moves_t MG_generatePawnMoves(uint8_t pawn_square, Board_t* board) {
  uint64_t is_white = B_squareToBitboard(pawn_square) & board->bitboard_data[W_P];
  uint64_t movement_squares = 0;

  // Only movement
  if (is_white) {
    uint8_t pawn_rank = B_getRank(pawn_square);
    if (pawn_rank == 2) {
      movement_squares = (white_pawn_moves[B_getFile(pawn_square)-1]) &
      ~maskRankXToRankY(3, 4, B_getAll(board));
    } else {
      uint8_t rank_offset = B_getRank(pawn_square) - 3;
      movement_squares = (white_pawn_moves[
        B_getFile(pawn_square) + 7
      ] << (rank_offset * 16)) & ~maskRankXToRankY(3, 4, B_getAll(board));
    }
  } else {
    uint8_t pawn_rank = B_getRank(pawn_square);
    if (pawn_rank == 7) {
      movement_squares = black_pawn_moves[B_getFile(pawn_square)-1] &
        ~maskRankXToRankY(6, 5, B_getAll(board));
    } else {
      uint8_t rank_offset = 6 - B_getRank(pawn_square);
      movement_squares = (black_pawn_moves[
        B_getFile(pawn_square) + 7
      ] >> (rank_offset * 16)) & ~maskRankXToRankY(6, 5, B_getAll(board));
    }
  }

  // Attack
  int8_t direction = is_white ? 1 : -1;
  uint64_t enemy = is_white ? B_getAllBlack(board) : B_getAllWhite(board);
  uint64_t attack_squares = pawn_attack_moves[B_getFile(pawn_square)-1]
    << (B_getRank(pawn_square) + direction) & enemy;
  uint8_t passant = board->passant_square;
  if (passant > 63) { // invalid / no unpassant
    uint64_t passant_board = B_squareToBitboard(passant);
    uint8_t passant_rank = B_getRank(passant);
    if (passant_rank == 3) {
      // a3 means black pawns can passant white
      if (passanting_pawns[B_getFile(pawn_square) - 1] & board->bitboard_data[B_P]) {
        attack_squares |= passant_board;
      }
    } else {
      // a6 means white pawns can passant black
      if ((passanting_pawns[B_getFile(pawn_square) - 1] << 8) & board->bitboard_data[W_P]) {
        attack_squares |= passant_board;
      }
    }
  }

  uint8_t movement_size = B_noOfPieces(movement_squares);
  uint8_t final_size = movement_size + B_noOfPieces(attack_squares);
  uint8_t* pm_final_positions = malloc(final_size);
  B_bitboardToSquares(pm_final_positions, 0, movement_squares);
  B_bitboardToSquares(pm_final_positions, movement_size, attack_squares);

  Player_t player = is_white ? P_White() : P_Black();
  Moves_t moves = MG_Moves_Init();
  for (int i = 0; i < final_size; i++) {
    uint8_t flag = i > movement_size ? CAPTURE : NONE;
    if (pm_final_positions[i] == passant) {
      flag |= EN_PASSANT;
    }
    MG_Moves_addMove(
      &moves,
      M_init(pawn_square, pm_final_positions[i], PAWN, player, flag)
    );
  }

  free(pm_final_positions);
  
  return moves;
}
