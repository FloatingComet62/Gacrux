#ifndef MOVE_H
#define MOVE_H

#include "player.h"
#include "piece.h"

typedef enum {
  /// Promote to Queen
  PROMOTE_Q   = 0b00000001,
  /// Promote to Rook
  PROMOTE_R   = 0b00000010,
  /// Promote to Bishop
  PROMOTE_B   = 0b00000100,
  /// Promote to Knight
  PROMOTE_N   = 0b00001000,

  /// Castling Kingside
  CASTLING_K  = 0b00010000,
  /// Castling Queenside
  CASTLING_Q  = 0b00100000,

  // Google En Passant
  // NOTE: Does require the capture flag
  EN_PASSANT  = 0b01000000,

  // Capturing of a piece
  CAPTURE     = 0b10000000
} eFlag_t;

/// # Move
/// * `initialSquare` - The square from where the piece moved
/// * `finalSquare` - The square to where the piece moved
/// * `piece` - The type of the piece that moved
/// * `player` - The player that made that move
/// * `flag` - Any addition information about the move
typedef struct {
  uint8_t initial_square;
  uint8_t final_square;
  ePiece_t piece;
  Player_t player;
  eFlag_t flag;
} Move_t;

Move_t M_init(
  uint8_t initial_square,
  uint8_t final_square,
  ePiece_t piece,
  Player_t player,
  eFlag_t flag
);

/// Convert the move into a string (mainly for printing purposes)
void M_print(Move_t* move);

#endif
