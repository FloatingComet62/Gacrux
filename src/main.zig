const std = @import("std");
const Board = @import("board.zig");
const Piece = Board.Piece;
const File = Board.File;
const Rank = Board.Rank;

pub fn main() !void {
    const stdout_file = std.io.getStdOut().writer();
    var bw = std.io.bufferedWriter(stdout_file);
    const stdout = bw.writer();

    const board = Board.starting_position();

    std.debug.print("{}", .{board[14].?});

    try stdout.print("Run `zig build test` to run the tests.\n", .{});

    try bw.flush();
}

test "Pieces align correctly" {
    std.debug.print("\nPieces align correctly\n", .{});
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
    std.debug.print("\nStarting position\n", .{});
    const board = Board.starting_position();
    std.debug.print("E1: {}\n", .{board[Board.square(.E, ._1)].?});
    std.debug.print("B8: {}\n", .{board[Board.square(.B, ._8)].?});
    std.debug.print("F7: {}\n", .{board[Board.square(.F, ._7)].?});
    std.debug.print("H1: {}\n", .{board[Board.square(.H, ._1)].?});
}
