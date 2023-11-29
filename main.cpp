#include "Board.hh"
#include "GameManager.hh"

int main(int argc, char *argv[])
{
  Board &board = Board::Instance();
  board.printBoard();

  GameManager *f = new GameManager();
  f->createWhitePieces();
  f->createBlackPieces();

  board.printBoard();

  delete f;

  std::cin.get();
}
