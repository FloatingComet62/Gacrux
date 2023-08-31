#ifndef PIECE_H
#define PIECE_H

typedef enum {
  NONE   = 0b000,

  PAWN   = 0b001,
  KNIGHT = 0b010,
  BISHOP = 0b011,
  ROOK   = 0b100,
  QUEEN  = 0b101,
  KING   = 0b110,
} ePiece_t;

/// Convert the piece into a string (mainly for printing purposes)
char* PI_print(ePiece_t piece);

#endif
