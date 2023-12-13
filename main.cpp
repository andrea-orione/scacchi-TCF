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
  board.printBoard();

  board.printWhitePieces();
  board.printBlackPieces();

  gm->getUserMove();

  delete gm;

  std::cin.get();
}
