#include "piece.h"

char* PI_print(ePiece_t piece) {
  if (NONE) {
    return "None";
  } else if (PAWN) {
    return "Pawn";
  } else if (KNIGHT) {
    return "Knight";
  } else if (BISHOP) {
    return "Bishop";
  } else if (QUEEN) {
    return "Queen";
  } else if (KING) {
    return "King";
  }
}
