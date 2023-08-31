#include "board.h"

#include <stdlib.h>

#include <stdio.h>
#include <inttypes.h>

CastlingRights_t B_startingCastling() {
  CastlingRights_t c = { 15 };
  return c;
}

void B_removeWhiteKingCastling(CastlingRights_t* castling_rights) {
  castling_rights->castling_data &= 0b0111;
}

void B_removeWhiteQueenCastling(CastlingRights_t* castling_rights) {
  castling_rights->castling_data &= 0b1011;
}

void B_removeBlackKingCastling(CastlingRights_t* castling_rights) {
  castling_rights->castling_data &= 0b1101;
}

void B_removeBlackQueenCastling(CastlingRights_t* castling_rights) {
  castling_rights->castling_data &= 0b1110;
}

void B_removeWhiteCastling(CastlingRights_t* castling_rights) {
  B_removeWhiteKingCastling(castling_rights);
  B_removeWhiteQueenCastling(castling_rights);
}

void B_removeBlackCastling(CastlingRights_t* castling_rights) {
  B_removeBlackKingCastling(castling_rights);
  B_removeBlackQueenCastling(castling_rights);
}

uint8_t B_getWhiteKingCastling(CastlingRights_t* castling_rights) {
  return castling_rights->castling_data >> 3;
}

uint8_t B_getWhiteQueenCastling(CastlingRights_t* castling_rights) {
  return (castling_rights->castling_data >> 2) & 1;
}

uint8_t B_getBlackKingCastling(CastlingRights_t* castling_rights) {
  return (castling_rights->castling_data >> 1) & 1;
}

uint8_t B_getBlackQueenCastling(CastlingRights_t* castling_rights) {
  return castling_rights->castling_data & 1;
}

char* B_castlingPrint(CastlingRights_t* castling_rights) {
  char* pm_output = malloc(5*sizeof(char));
  pm_output[4] = '\0';
  if (B_getWhiteKingCastling(castling_rights)) {
    pm_output[0] = 'K';
  } else {
    pm_output[0] = ' ';
  }

  if (B_getBlackKingCastling(castling_rights)) {
    pm_output[1] = 'k';
  } else {
    pm_output[1] = ' ';
  }

  if (B_getWhiteQueenCastling(castling_rights)) {
    pm_output[2] = 'Q';
  } else {
    pm_output[2] = ' ';
  }

  if (B_getBlackQueenCastling(castling_rights)) {
    pm_output[3] = 'q';
  } else {
    pm_output[3] = ' ';
  }

  return pm_output;
}

Board_t B_startingPosition() {
  uint64_t bitboard_data[12] = {
    0x0000000000000010LL, // W_K
    0x1000000000000000LL, // B_K
    0x0000000000000008LL, // W_Q
    0x0800000000000000LL, // B_Q
    0x0000000000000081LL, // W_R
    0x8100000000000000LL, // B_R
    0x0000000000000024LL, // W_B
    0x2400000000000000LL, // B_B
    0x0000000000000042LL, // W_N
    0x4200000000000000LL, // B_N
    0x000000000000FF00LL, // W_P
    0x00FF000000000000LL, // B_P
  };
  Player_t player = P_White();
  CastlingRights_t castling_rights = B_startingCastling();
  Board_t x = {
    bitboard_data, player, castling_rights, 0, 0, 1
  };
  return x;
}
uint64_t B_getAll(Board_t* board) {
  return B_getAllWhite(board) || B_getAllBlack(board);
}

uint64_t B_getAllWhite(Board_t* board) {
  return B_getWhiteKing(board) || B_getWhiteQueen(board) ||
  B_getWhiteRook(board) || B_getWhiteBishop(board) ||
  B_getWhiteKnight(board) || B_getWhitePawn(board);
}

uint64_t B_getWhiteKing(Board_t* board) {
  return board->bitboard_data[W_K];
}

uint64_t B_getWhiteQueen(Board_t* board) {
  return board->bitboard_data[W_Q];
}

uint64_t B_getWhiteRook(Board_t* board) {
  return board->bitboard_data[W_R];
}

uint64_t B_getWhiteBishop(Board_t* board) {
  return board->bitboard_data[W_B];
}

uint64_t B_getWhiteKnight(Board_t* board) {
  return board->bitboard_data[W_K];
}

uint64_t B_getWhitePawn(Board_t* board) {
  return board->bitboard_data[W_P];
}

uint64_t B_getAllBlack(Board_t* board) {
  return B_getBlackKing(board) || B_getBlackQueen(board) ||
  B_getBlackRook(board) || B_getBlackBishop(board) ||
  B_getBlackKnight(board)|| B_getBlackPawn(board);
}

uint64_t B_getBlackKing(Board_t* board) {
  return board->bitboard_data[B_K];
}

uint64_t B_getBlackQueen(Board_t* board) {
  return board->bitboard_data[B_Q];
}

uint64_t B_getBlackRook(Board_t* board) {
  return board->bitboard_data[B_R];
}

uint64_t B_getBlackBishop(Board_t* board) {
  return board->bitboard_data[B_B];
}

uint64_t B_getBlackKnight(Board_t* board) {
  return board->bitboard_data[B_K];
}

uint64_t B_getBlackPawn(Board_t* board) {
  return board->bitboard_data[B_P];
}

uint8_t B_getRank(uint8_t square) {
  return (square / 8) + 1;
}

uint8_t B_getFile(uint8_t square) {
  return (square + 1) % 8;
}

uint64_t B_squareToBitboard(uint8_t square) {
  return 1 << square;
}

uint8_t B_noOfPieces(uint64_t board) {
  uint8_t no_of_pieces = 0;
  for (int i = 0; i < 64; i++) {
    if((board >> i) % 2) {
      no_of_pieces++;
    }
  }
  return no_of_pieces;
}

void B_bitboardToSquares(uint8_t* buffer, uint8_t buffer_start, uint64_t board) {
  int index_of_buffer = buffer_start;
  for (int i = 0; i < 64; i++) {
    if ((board >> i) % 2) {
      buffer[index_of_buffer] = i;
      index_of_buffer++;
    }
  }
}

char B_filePrint(uint8_t file) {
  return 'a' - 1 + file;
}

char B_rankPrint(uint8_t rank) {
  return '0' + rank;
}

char* B_squarePrint(uint8_t square) {
  uint8_t rank = B_getRank(square);
  uint8_t file = B_getFile(square);

  char* pm_string = malloc(3 * sizeof(char));
  pm_string[0] = B_filePrint(file);
  pm_string[1] = B_rankPrint(rank);
  pm_string[2] = '\0';

  return pm_string;
}

void B_print(Board_t* board) {
  printf(
    "{\n"
    "\tbitboard_data: [\n"
    "\t\t%"PRIu64",\n"
    "\t\t%"PRIu64",\n"
    "\t\t%"PRIu64",\n"
    "\t\t%"PRIu64",\n"
    "\t\t%"PRIu64",\n"
    "\t\t%"PRIu64",\n"
    "\t\t%"PRIu64",\n"
    "\t\t%"PRIu64",\n"
    "\t\t%"PRIu64",\n"
    "\t\t%"PRIu64",\n"
    "\t\t%"PRIu64",\n"
    "\t\t%"PRIu64",\n"
    "\t],\n"
    "\tplayer: %s,\n"
    "\thalfmove_clock: %"PRIu8"\n"
    "\tpassant_square: %s\n"
    "\tcastling_rights: %s\n"
    "\tfullmove_clock: %"PRIu16"\n"
    "}\n",
    board->bitboard_data[W_K],
    board->bitboard_data[B_K],
    board->bitboard_data[W_Q],
    board->bitboard_data[B_Q],
    board->bitboard_data[W_R],
    board->bitboard_data[B_R],
    board->bitboard_data[W_B],
    board->bitboard_data[B_B],
    board->bitboard_data[W_N],
    board->bitboard_data[B_N],
    board->bitboard_data[W_P],
    board->bitboard_data[B_P],

    P_print(&board->player),
    board->halfmove_clock,
    B_squarePrint(board->passant_square),
    B_castlingPrint(&board->castling_rights),
    board->fullmove_number
  );
}
