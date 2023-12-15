#include "Board.hh"
#include "Coordinate.hh"
#include "GameManager.hh"
#include <string>
#include <vector>
#include <iostream>

int main(int argc, char *argv[])
{
  Board &board = Board::Instance();

  GameManager *gm = new GameManager();

  gm->InitializeStartingBoard();

  while (true)
  {
    board.printWhiteInterface();
    // board.printBlackInterface();
    // board.printDoubleInterface();
    gm->getUserMove();
  }

  delete gm;

  std::cin.get();
}
