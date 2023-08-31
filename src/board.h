#ifndef BOARD_H
#define BOARD_H

#include "move.h"

#define RANK_1 0x00000000000000FFLL
#define RANK_2 0x000000000000FF00LL
#define RANK_3 0x0000000000FF0000LL
#define RANK_4 0x00000000FF000000LL
#define RANK_5 0x000000FF00000000LL
#define RANK_6 0x0000FF0000000000LL
#define RANK_7 0x00FF000000000000LL
#define RANK_8 0xFF00000000000000LL

#define FILE_A 0x0101010101010101LL
#define FILE_B 0x0202020202020202LL
#define FILE_C 0x0404040404040404LL
#define FILE_D 0x0808080808080808LL
#define FILE_E 0x1010101010101010LL
#define FILE_F 0x2020202020202020LL
#define FILE_G 0x4040404040404040LL
#define FILE_H 0x8080808080808080LL

#define W_K 0
#define W_Q 2
#define W_R 4
#define W_B 6
#define W_N 8
#define W_P 10

#define B_K 1
#define B_Q 3
#define B_R 5
#define B_B 7
#define B_N 9
#define B_P 11

/// # CastlingRights
/// `castling_data` - 0babcd
/// a - white_king_castling
/// b - white_queen_castling
/// c - black_king_castling
/// d - black_queen_castling
typedef struct {
  uint8_t castling_data;
} CastlingRights_t;

CastlingRights_t B_startingCastling();

void B_removeWhiteKingCastling(CastlingRights_t* castling_rights);
void B_removeWhiteQueenCastling(CastlingRights_t* castling_rights);

void B_removeBlackKingCastling(CastlingRights_t* castling_rights);
void B_removeBlackQueenCastling(CastlingRights_t* castling_rights);

void B_removeWhiteCastling(CastlingRights_t* castling_rights);
void B_removeBlackCastling(CastlingRights_t* castling_rights);

uint8_t B_getWhiteKingCastling(CastlingRights_t* castling_rights);
uint8_t B_getWhiteQueenCastling(CastlingRights_t* castling_rights);

uint8_t B_getBlackKingCastling(CastlingRights_t* castling_rights);
uint8_t B_getBlackQueenCastling(CastlingRights_t* castling_rights);

/// Convert the board into a string (mainly for printing purposes)
char* B_castlingPrint(CastlingRights_t* board);

/// # Board
/// * `bitboard_data` - All the piece positions on a bitboard
/// * `player` - The player whose turn it is
/// * `castling_rights` - Castling Rights of both the sides
/// * `passant_square` - That french move ( > 63 if no passanting )
/// * `halfmove_clock` - The FEN code informs how many moves both players have made since the last pawn advance or piece capture. When this counter reaches 100 (allowing each player to make 50 moves), the game ends in a draw.
/// * `fullmove_number` - The FEN code shows the number of completed turns in the game. This number is incremented by one every time Black moves.
typedef struct {
  uint64_t* bitboard_data;
  Player_t player;
  CastlingRights_t castling_rights;
  uint8_t passant_square;
  uint8_t halfmove_clock;
  int16_t fullmove_number;
} Board_t;

Board_t B_startingPosition();
uint64_t B_getAll(Board_t* board);

uint64_t B_getAllWhite(Board_t* board);
uint64_t B_getWhiteKing(Board_t* board);
uint64_t B_getWhiteQueen(Board_t* board);
uint64_t B_getWhiteRook(Board_t* board);
uint64_t B_getWhiteBishop(Board_t* board);
uint64_t B_getWhiteKnight(Board_t* board);
uint64_t B_getWhitePawn(Board_t* board);

uint64_t B_getAllBlack(Board_t* board);
uint64_t B_getBlackKing(Board_t* board);
uint64_t B_getBlackQueen(Board_t* board);
uint64_t B_getBlackRook(Board_t* board);
uint64_t B_getBlackBishop(Board_t* board);
uint64_t B_getBlackKnight(Board_t* board);
uint64_t B_getBlackPawn(Board_t* board);

uint8_t B_getRank(uint8_t square);
uint8_t B_getFile(uint8_t square);

/// Convert a square to a board
uint64_t B_squareToBitboard(uint8_t square);

/// Get the number of pieces on the board
uint8_t B_noOfPieces(uint64_t board);

/// Get the squares from the board
/// * `buffer` - Buffer for squars
/// * `buffer_start` - The index from which the function should start appending
/// * `board` - The board from which you want the squares
void B_bitboardToSquares(uint8_t* buffer, uint8_t buffer_start, uint64_t board);

/// Convert the file into a string (mainly for printing purposes)
char B_filePrint(uint8_t file);

/// Convert the rank into a string (mainly for printing purposes)
char B_rankPrint(uint8_t rank);

/// Convert the square into a string (mainly for printing purposes)
char* B_squarePrint(uint8_t square);

/// Convert the board into a string (mainly for printing purposes)
void B_print(Board_t* board);

#endif
