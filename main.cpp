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
  std::cout <<board.getPiece(Coordinate(2,1))->toString() << std::endl;
  std::cout <<board.getPiece(Coordinate(2,1))->getPosition().getX() << std::endl;
  board.printBoard();

  board.printWhitePieces();
  board.printBlackPieces();

  std::cout <<board.getPiece(Coordinate(2,1))->toString() << std::endl;
  std::cout <<board.getPiece(Coordinate(2,1))->getPosition().getX() << std::endl;

  gm->getUserMove();

  std::cout << "CheckPoint";

  delete gm;

  std::cin.get();
}
