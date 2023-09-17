use chess::{Board, ChessMove, MoveGen};
// use std::thread;

/// +ve is better for white
/// -ve is better for black
fn eval(_board: &Board) -> f32 {
    return 0.0;
}

#[derive(Clone, Copy)]
pub struct Search {
    pub initial_board: Board,
    pub best_move: Option<ChessMove>,
    pub best_eval: Option<f32>,
    pub searching: bool,
}

impl Search {
    pub fn new(initial_board: Board) -> Self {
        Self {
            initial_board,
            best_move: None,
            best_eval: None,
            searching: false,
        }
    }
    fn search(&self, board: &Board, depth: u8) -> Option<f32> {
        if !self.searching {
            return None;
        }

        let iter = MoveGen::new_legal(board);
        let mut best_eval: f32 = -f32::INFINITY;
        for chess_move in iter {
            let new_board = board.make_move_new(chess_move);
            if depth == 0 {
                // evaluate the position
                let current_eval = eval(&new_board);
                if current_eval > best_eval {
                    best_eval = current_eval
                }
                continue;
            }
            let current_eval = self.search(&new_board, depth - 1);
            match current_eval {
                None => continue,
                Some(eval) => {
                    if -eval > best_eval {
                        best_eval = -eval;
                    }
                }
            }
        }
        return Some(best_eval);
    }
    pub fn start_search(&'static mut self, depth: u8) {
        self.searching = true;

        let iter = MoveGen::new_legal(&self.initial_board);

        for chess_move in iter {
            let pos_eval = self.search(&self.initial_board.make_move_new(chess_move), depth - 1);
            match pos_eval {
                None => {}
                Some(eval) => {
                    if eval > self.best_eval.unwrap_or(-f32::INFINITY) {
                        self.best_eval = Some(eval);
                        self.best_move = Some(chess_move);
                    }
                }
            }
        }
    }
}
