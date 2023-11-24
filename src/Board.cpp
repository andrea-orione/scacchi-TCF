#include "../include/Board.hh"
#include "../include/Coordinate.hh"
#include <map>
#include <iostream>
#include <vector>

Board::Board():
  squaresVector(std::vector<Square>(64)),
  squaresMap(std::map<Coordinate, Square>()){
  for (int row=1; row<9; row++) {
    for (int column=1; column<9; column++) {
      std::pair<Coordinate, Square> squareCoordPair(Coordinate(row, column), Square()); 
    }
  }
}

void Board::printBoard() {
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
