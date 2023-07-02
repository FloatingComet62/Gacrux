typedef enum {
  PAWN,
  KNIGHT,
  BISHOP,
  ROOK,
  QUEEN,
  KING
} ePiece_t;

typedef enum {
  WHITE,
  BLACK
} ePlayer_t;

typedef enum {
  /// Promote to Queen
  PROMOTE_Q,
  /// Promote to Rook
  PROMOTE_R,
  /// Promote to Bishop
  PROMOTE_B,
  /// Promote to Knight
  PROMOTE_N,

  /// Castling Kingside
  CASTLING_K,
  /// Castling Queenside
  CASTLING_Q,

  EN_PASSANT
} eFlag_t;

/// # Move
/// * `initialSquare` - The square from where the piece moved
/// * `finalSquare` - The square to where the piece moved
/// * `piece` - The type of the piece that moved
/// * `player` - The player that made that move
/// * `flag` - Any addition information about the move
typedef struct {
  uint8_t initialSquare;
  uint8_t finalSquare;
  ePiece_t piece;
  ePlayer_t player;
  eFlag_t flag;
} Move_t;