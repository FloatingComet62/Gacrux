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
    pub fn get(self: Self, square: Square) ?Piece {
        return self.pieces[square.to_index()];
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

pub const File = enum(u3) {
    const Self = @This();
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    pub fn to_str(self: Self) u8 {
        return switch (self) {
            .A => 'A',
            .B => 'B',
            .C => 'C',
            .D => 'D',
            .E => 'E',
            .F => 'F',
            .G => 'G',
            .H => 'H',
        };
    }
    pub fn from_str(self: u8) ?Self {
        return switch (self) {
            'A' => .A,
            'B' => .B,
            'C' => .C,
            'D' => .D,
            'E' => .E,
            'F' => .F,
            'G' => .G,
            'H' => .H,
            'a' => .A,
            'b' => .B,
            'c' => .C,
            'd' => .D,
            'e' => .E,
            'f' => .F,
            'g' => .G,
            'h' => .H,
            else => null,
        };
    }
};
pub const Rank = enum(u3) {
    const Self = @This();
    _1,
    _2,
    _3,
    _4,
    _5,
    _6,
    _7,
    _8,
    pub fn to_str(self: Self) u8 {
        return switch (self) {
            ._1 => '1',
            ._2 => '2',
            ._3 => '3',
            ._4 => '4',
            ._5 => '5',
            ._6 => '6',
            ._7 => '7',
            ._8 => '8',
        };
    }
    pub fn from_str(self: u8) ?Self {
        return switch (self) {
            '1' => ._1,
            '2' => ._2,
            '3' => ._3,
            '4' => ._4,
            '5' => ._5,
            '6' => ._6,
            '7' => ._7,
            '8' => ._8,
            else => null,
        };
    }
};

pub const Square = struct {
    const Self = @This();
    file: File,
    rank: Rank,

    pub fn init(file: File, rank: Rank) Self {
        return Self{ .file = file, .rank = rank };
    }
    pub fn from_str(str: *const [2]u8) ?Self {
        const file = File.from_str(str[0]);
        const rank = Rank.from_str(str[1]);
        return Self{
            .file = file orelse (return null),
            .rank = rank orelse (return null),
        };
    }
    pub fn to_str(self: Self) [2]u8 {
        return [2]u8{ self.file.to_str(), self.rank.to_str() };
    }
    pub fn to_index(self: Self) u6 {
        return @intFromEnum(self.file) + @as(u6, @intFromEnum(self.rank)) * 8;
    }
    pub fn is_equal(square1: Self, square2: Self) bool {
        return square1.file == square2.file and square1.rank == square2.rank;
    }
};

pub const Move = struct {
    const Self = @This();
    from: Square,
    to: Square,

    pub fn init(from: Square, to: Square) Self {
        return Self{ .from = from, .to = to };
    }
    pub fn from_str(str: *const [4]u8) ?Self {
        const from = Square.from_str(str[0..2]);
        const to = Square.from_str(str[2..]);
        return Self{
            .from = from orelse (return null),
            .to = to orelse (return null),
        };
    }
    pub fn to_str(self: Self) [4]u8 {
        return self.from.to_str() ++ self.to.to_str();
    }
    pub fn is_equal(move1: Self, move2: Self) bool {
        return Square.is_equal(move1.from, move2.from) and
            Square.is_equal(move1.to, move2.to);
    }
};
