const std = @import("std");

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
pub const PiecePresentable = enum(u4) {
    W_KING,
    W_QUEEN,
    W_ROOK,
    W_BISHOP,
    W_KNIGHT,
    W_PAWN,
    B_KING,
    B_QUEEN,
    B_ROOK,
    B_BISHOP,
    B_KNIGHT,
    B_PAWN,
};

pub const Board = struct {
    const Self = @This();

    pieces: [64]?Piece,
    pub fn starting_position() Self {
        return .{
            .pieces = .{
                .W_CASTLEABLE_ROOK, .W_KNIGHT, .W_BISHOP, .W_QUEEN, .W_KING, .W_BISHOP, .W_KNIGHT, .W_CASTLEABLE_ROOK,
                .W_PAWN,            .W_PAWN,   .W_PAWN,   .W_PAWN,  .W_PAWN, .W_PAWN,   .W_PAWN,   .W_PAWN,
                null,               null,      null,      null,     null,    null,      null,      null,
                null,               null,      null,      null,     null,    null,      null,      null,
                null,               null,      null,      null,     null,    null,      null,      null,
                null,               null,      null,      null,     null,    null,      null,      null,
                .B_PAWN,            .B_PAWN,   .B_PAWN,   .B_PAWN,  .B_PAWN, .B_PAWN,   .B_PAWN,   .B_PAWN,
                .B_CASTLEABLE_ROOK, .B_KNIGHT, .B_BISHOP, .B_QUEEN, .B_KING, .B_BISHOP, .B_KNIGHT, .B_CASTLEABLE_ROOK,
            },
        };
    }
    pub fn null_position() Self {
        return .{
            .pieces = .{
                null, null, null, null, null, null, null, null,
                null, null, null, null, null, null, null, null,
                null, null, null, null, null, null, null, null,
                null, null, null, null, null, null, null, null,
                null, null, null, null, null, null, null, null,
                null, null, null, null, null, null, null, null,
                null, null, null, null, null, null, null, null,
                null, null, null, null, null, null, null, null,
            },
        };
    }
    pub fn get(self: Self, file: File, rank: Rank) ?Piece {
        return self.pieces[square(file, rank)];
    }
    pub fn get_piece_positions(self: Self, allocator: std.mem.Allocator, piece: Piece, count: ?u6) ![]u6 {
        const actual_count = count orelse 10;
        var squares = try std.ArrayList(u6).initCapacity(allocator, actual_count);
        for (0.., self.pieces) |i, board_pieces| {
            if (piece != board_pieces) {
                continue;
            }
            squares.appendAssumeCapacity(@intCast(i));
            if (squares.items.len == actual_count) {
                break;
            }
        }
        return squares.items;
    }
    pub fn generate_raw_bitboards(self: Self) [16]u64 {
        var bitboards = [16]u64{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        for (0.., self.pieces) |i, maybe_piece| {
            const piece = maybe_piece orelse continue;
            bitboards[@intFromEnum(piece)] |= @as(u64, 1) << @intCast(i);
        }
        return bitboards;
    }
    pub fn generate_bitboards(self: Self) *[12]u64 {
        var bitboards = self.generate_raw_bitboards();
        return bitboards[0..2] ++ .{bitboards[2] | bitboards[3]} // White Rooks
        ++ bitboards[4..6] ++ .{bitboards[6] | bitboards[7]} // White Pawns
        ++ bitboards[8..10] ++ .{bitboards[10] | bitboards[11]} // Black Rooks
        ++ bitboards[12..14] ++ .{bitboards[14] | bitboards[15]} // Black Pawns
        ;
    }
};

pub const File = enum(u3) { A, B, C, D, E, F, G, H };
pub const Rank = enum(u3) { _1, _2, _3, _4, _5, _6, _7, _8 };

pub fn square(file: File, rank: Rank) u6 {
    return @intFromEnum(file) + @as(u6, @intFromEnum(rank)) * 8;
}
