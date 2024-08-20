pub const Piece = enum(u4) {
    W_KING,
    W_QUEEN,
    W_ROOK,
    W_CASTLEABLE_ROOK,
    W_BISHOP,
    W_KNIGHT,
    W_PAWN,
    W_PASSANTABLE_PAWN,
    B_KING,
    B_QUEEN,
    B_ROOK,
    B_CASTLEABLE_ROOK,
    B_BISHOP,
    B_KNIGHT,
    B_PAWN,
    B_PASSANTABLE_PAWN,
};

pub fn starting_position() [64]?Piece {
    const board = [64]?Piece{
        .W_CASTLEABLE_ROOK, .W_KNIGHT, .W_BISHOP, .W_QUEEN, .W_KING, .W_BISHOP, .W_KNIGHT, .W_CASTLEABLE_ROOK,
        .W_PAWN,            .W_PAWN,   .W_PAWN,   .W_PAWN,  .W_PAWN, .W_PAWN,   .W_PAWN,   .W_PAWN,
        null,               null,      null,      null,     null,    null,      null,      null,
        null,               null,      null,      null,     null,    null,      null,      null,
        null,               null,      null,      null,     null,    null,      null,      null,
        null,               null,      null,      null,     null,    null,      null,      null,
        .B_PAWN,            .B_PAWN,   .B_PAWN,   .B_PAWN,  .B_PAWN, .B_PAWN,   .B_PAWN,   .B_PAWN,
        .B_CASTLEABLE_ROOK, .B_KNIGHT, .B_BISHOP, .B_QUEEN, .B_KING, .B_BISHOP, .B_KNIGHT, .B_CASTLEABLE_ROOK,
    };
    return board;
}

pub const File = enum(u3) { A, B, C, D, E, F, G, H };
pub const Rank = enum(u3) { _1, _2, _3, _4, _5, _6, _7, _8 };

pub fn square(file: File, rank: Rank) u7 {
    return @intFromEnum(file) + @as(u7, @intFromEnum(rank)) * 8;
}
