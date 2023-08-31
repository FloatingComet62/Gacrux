#include "player.h"

void P_switchTurn(Player_t* player) {
  player->data = ~player->data;
}

Player_t P_White() {
  Player_t p = { 1 };
  return p;
}

Player_t P_Black() {
  Player_t p = { 0 };
  return p;
}

char* P_print(Player_t* player) {
  if (player->data == 1) {
    return "White";
  } else {
    return "Black";
  }
}
