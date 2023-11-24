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
      std::pair<Coordinate, Square> squareCoordPair(Coordinate(column, row), Square());
      squaresMap.insert(squareCoordPair);
    }
  }
}

void Board::printBoard() {
  //Slightly inefficient but the code is cleaner
  std::cout << "\n   ╔═══╤═══╤═══╤═══╤═══╤═══╤═══╤═══╗\n";
  for (int row=8; row>0; row--) {
    std::cout << " " << row << " ║ ";
    for (int column=1; column<9; column++)
    {
      squaresMap[Coordinate(column,row)].printSquareContent();
      if (column == 8) std::cout << " ║";
      else std::cout << " │ ";
    }
    std::cout << "\n   ";
    if (row == 1) std::cout << "╚═══╧═══╧═══╧═══╧═══╧═══╧═══╧═══╝\n";
    else std::cout << "╟───┼───┼───┼───┼───┼───┼───┼───╢\n";
  }
  std::cout << "     a   b   c   d   e   f   g   h\n\n"; 
}
