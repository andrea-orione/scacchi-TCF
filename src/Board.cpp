#include "../include/Board.hh"
#include <iostream>
#include <vector>

Board::Board():
  squaresVector(std::vector<Square>(64))
{

}

void Board::printBoard()
{
  std::cout << " ---------------------------------\n";
  for (int row=7; row>-1; row--) {
    std::cout << " |";
    for (int column=0; column<8; column++)
    {
      std::cout << " ";
      squaresVector[row*8+column].printSquareContent();
      std::cout << " |";
    }
    std::cout << "\n ---------------------------------\n";
  }
}
