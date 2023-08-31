#ifndef NOTATION_H
#define NOTATION_H

#include "board.h"

/// Get the square from the notation
uint8_t N_square(char* notation);

/// Get the board from the fen notation
///! WARNING: THIS FUNCTION DOESN'T CHECK IF THE FEN IS VALID OR NOT
///
/// Starting board fen: rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
/// Phase 1 -> Piece Positions
/// Phase 2 -> Player whose turn it is
/// Phase 3 -> Castling Data
/// Phase 4 -> Passant Square
/// Phase 5 -> Halfmove Clock : The FEN code informs how many moves both players have made since the last pawn advance or piece capture. When this counter reaches 100 (allowing each player to make 50 moves), the game ends in a draw.
/// Phase 6 -> Fullmove Number : The FEN code shows the number of completed turns in the game. This number is incremented by one every time Black moves.
Board_t N_board(char* fen);

#endif
