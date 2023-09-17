use chess::Board;
use no_panic::no_panic;

pub mod search;

#[no_panic]
fn main() {
    let _board = Board::default();
}
