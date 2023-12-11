#include "Board.hh"
#include "Coordinate.hh"
#include "GameManager.hh"
#include <string>
#include <vector>
#include <iostream>

int main(int argc, char *argv[])
{
  Board &board = Board::Instance();

  GameManager *f = new GameManager();

  f->InitializeStartingBoard();
  board.printBoard();

  board.printWhitePieces();
  board.printBlackPieces();

  std::cout << board.getPiece(Coordinate(1,1))->toString();

  delete f;

  std::cin.get();
}
