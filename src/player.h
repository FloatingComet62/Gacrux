#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>

/// # Player
/// `data` - 0ba
/// a - 1 means white, 0 means black
typedef struct {
  uint8_t data;
} Player_t;

/// If it was black's turn, it becomes white's turn
/// If it was white's turn, it becomes black's turn
void P_switchTurn(Player_t* player);

/// A reference for white player
Player_t P_White();

/// A reference for black player
Player_t P_Black();

/// Convert the player into a string (mainly for printing purposes)
char* P_print(Player_t* player);

#endif
