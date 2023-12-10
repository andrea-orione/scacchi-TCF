#include "Board.hh"
#include "GameManager.hh"
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
  Board &board = Board::Instance();

  GameManager *f = new GameManager();

  f->InitializeStartingBoard();
  board.printBoard();

  delete f;

  std::cin.get();
}
