#include "../include/Board.hh"
#include <iostream>
#include <vector>

Board::Board():
  squaresVector(std::vector<Square>(64))
{

}

void Board::printBoard()
{
  //Slightly inefficient but the code is cleaner
  std::cout << "   ╔═══╤═══╤═══╤═══╤═══╤═══╤═══╤═══╗\n";
  for (int row=7; row>-1; row--) {
    std::cout << " " << row+1 << " ║ ";
    for (int column=0; column<8; column++)
    {
      squaresVector[row*8+column].printSquareContent();
      if (column == 7) std::cout << " ║";
      else std::cout << " │ ";
    }
    std::cout << "\n   ";
    if (row == 0) std::cout << "╚═══╧═══╧═══╧═══╧═══╧═══╧═══╧═══╝\n";
    else std::cout << "╟───┼───┼───┼───┼───┼───┼───┼───╢\n";
  }
  std::cout << "     1   2   3   4   5   6   7   8\n"; 
}
