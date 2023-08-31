#include "notation.h"
#include "board.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <inttypes.h>

uint8_t N_square(char* notation) {
  uint8_t file = notation[0] - 'a';
  uint8_t rank = notation[1] - '0';

  return (rank - 1) * 8 + file;
}

Board_t N_board(char* fen) {
  uint8_t fen_size = strlen(fen);
  uint64_t bitboard_data[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t index = 0;
  uint8_t rank = 8;
  uint64_t currentBitboard = 1;
  currentBitboard <<= (rank - 1) * 8;
  while (1) {
    char character = fen[index];
    if (character == 'K') {
      bitboard_data[W_K] |= currentBitboard;
    } else if (character == 'Q') {
      bitboard_data[W_Q] |= currentBitboard;
    } else if (character == 'R') {
      bitboard_data[W_R] |= currentBitboard;
    } else if (character == 'B') {
      bitboard_data[W_B] |= currentBitboard;
    } else if (character == 'N') {
      bitboard_data[W_N] |= currentBitboard;
    } else if (character == 'P') {
      bitboard_data[W_P] |= currentBitboard;
    } else if (character == 'k') {
      bitboard_data[B_K] |= currentBitboard;
    } else if (character == 'q') {
      bitboard_data[B_Q] |= currentBitboard;
    } else if (character == 'r') {
      bitboard_data[B_R] |= currentBitboard;
    } else if (character == 'b') {
      bitboard_data[B_B] |= currentBitboard;
    } else if (character == 'n') {
      bitboard_data[B_N] |= currentBitboard;
    } else if (character == 'p') {
      bitboard_data[B_P] |= currentBitboard;
    } else if (character == '/') {
      rank--;
      currentBitboard = 1;
      currentBitboard <<= (rank - 1) * 8;

      index++;
      continue;
    } else if (character == ' ') {
      index++;
      break;
    } else {
      int numberOfSkips = character - '0';
      currentBitboard <<= numberOfSkips;

      index++;
      continue;
    }

    // TO PREVENT INTEGER OVERFLOW
    // 1 << 63 is the same as
    // 2147483648 << 32
    // This is to avoid Shift >= Width Count warning
    if (currentBitboard < (2147483648 << 32)) {
      currentBitboard <<= 1;
    }
    index++;
  }

  Player_t player;
  if (fen[index] == 'w') {
    player = P_White();
  } else {
    player = P_Black();
  }
  index += 2;


  CastlingRights_t castling_rights = B_startingCastling();
  while (1) {
    char character = fen[index];

    if (character == 'K') {
      castling_rights.castling_data |= 0b1000;
    } else if (character == 'k') {
      castling_rights.castling_data |= 0b0010;
    } else if (character == 'Q') {
      castling_rights.castling_data |= 0b0100;
    } else if (character == 'q') {
      castling_rights.castling_data |= 0b0001;
    } else if (character == ' ') {
      index++;
      break;
    }

    index++;
  }
  
  uint8_t passant = 255;
  if (fen[index] != '-') {
    passant = N_square((char[2]){fen[index], fen[index+1]});
    index += 3;
  } else {
    index += 2;
  }

  uint8_t index_clone = index;
  while (1) {
    if (fen[index_clone] == ' ') {
      break;
    }
    index_clone++;
  }
  char halfmove_clock_string[index_clone-index];
  uint8_t i = 0;
  while (index_clone > index) {
    halfmove_clock_string[i] = fen[index];
    i++;
    index++;
  }
  uint16_t halfmove_clock = atoi(halfmove_clock_string);

  index++;

  char fullmove_number_string[fen_size-index];
  i = 0;
  while (fen_size < index) {
    printf("%c\n", fen[index]); // !
    fullmove_number_string[i] = fen[index];
    index++;
    i++;
  }
  uint16_t fullmove_number = atoi(fullmove_number_string);

  Board_t board = {
    bitboard_data,
    player,
    castling_rights,
    passant,
    halfmove_clock,
    fullmove_number
  };

  B_print(&board);
  return board;
}
