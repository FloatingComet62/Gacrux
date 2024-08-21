const std = @import("std");
const testing = std.testing;
const BoardData = @import("board.zig");
const Piece = BoardData.Piece;
const PiecePresentable = BoardData.PiecePresentable;
const Board = BoardData.Board;

export fn add(a: i32, b: i32) i32 {
    return a + b;
}

test "basic add functionality" {
    try testing.expect(add(3, 7) == 10);
}

test "Pieces alignment" {
    std.debug.print("\nPieces alignment\n", .{});
    std.debug.print("Piece\t\t\t |Value\n", .{});
    std.debug.print("-------------------------|-------\n", .{});
    std.debug.print("White King\t\t |{}\n", .{@intFromEnum(Piece.W_KING)});
    std.debug.print("White Queen\t\t |{}\n", .{@intFromEnum(Piece.W_QUEEN)});
    std.debug.print("White Rook\t\t |{}\n", .{@intFromEnum(Piece.W_ROOK)});
    std.debug.print("White Rook(Castleable)   |{}\n", .{@intFromEnum(Piece.W_CASTLEABLE_ROOK)});
    std.debug.print("White Bishop\t\t |{}\n", .{@intFromEnum(Piece.W_BISHOP)});
    std.debug.print("White Knight\t\t |{}\n", .{@intFromEnum(Piece.W_KNIGHT)});
    std.debug.print("White Pawn\t\t |{}\n", .{@intFromEnum(Piece.W_PAWN)});
    std.debug.print("White Pawn(Passantable)  |{}\n", .{@intFromEnum(Piece.W_PASSANTABLE_PAWN)});
    std.debug.print("Black King\t\t |{}\n", .{@intFromEnum(Piece.B_KING)});
    std.debug.print("Black Queen\t\t |{}\n", .{@intFromEnum(Piece.B_QUEEN)});
    std.debug.print("Black Rook\t\t |{}\n", .{@intFromEnum(Piece.B_ROOK)});
    std.debug.print("Black Rook(Castleable)   |{}\n", .{@intFromEnum(Piece.B_CASTLEABLE_ROOK)});
    std.debug.print("Black Bishop\t\t |{}\n", .{@intFromEnum(Piece.B_BISHOP)});
    std.debug.print("Black Knight\t\t |{}\n", .{@intFromEnum(Piece.B_KNIGHT)});
    std.debug.print("Black Pawn\t\t |{}\n", .{@intFromEnum(Piece.B_PAWN)});
    std.debug.print("Black Pawn(Passantable)  |{}\n", .{@intFromEnum(Piece.B_PASSANTABLE_PAWN)});
}

test "Starting position" {
    const board = Board.starting_position();
    try testing.expect(board.get(.E, ._1).? == .W_KING);
    try testing.expect(board.get(.B, ._8).? == .B_KNIGHT);
    try testing.expect(board.get(.F, ._7).? == .B_PAWN);
    try testing.expect(board.get(.H, ._1).? == .W_CASTLEABLE_ROOK);
    try testing.expect(board.get(.H, ._8).? == .B_CASTLEABLE_ROOK);
}

test "Piece Position Pickup" {
    const board = Board.starting_position();
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    try testing.expect((try board.get_piece_positions(arena.allocator(), .W_KING, 1))[0] == 4);
}

test "Bitboard Generation" {
    std.debug.print("\nBitboard Generation\n", .{});
    const board = Board.starting_position();
    for (0..12) |i| {
        std.debug.print("{}: {b}\n", .{ @as(PiecePresentable, @enumFromInt(i)), board.generate_bitboards()[i] });
    }
    try testing.expect(board.generate_bitboards()[2] == 0b10000001);
    try testing.expect(board.generate_bitboards()[4] == 0b01000010);
}
