#include "Board.hh"
#include "GameManager.hh"
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
  Board &board = Board::Instance();

  GameManager *f = new GameManager();

  f->loadFenPosition("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
  board.printBoard();

  delete f;

  std::cin.get();
}
