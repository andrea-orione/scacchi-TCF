#include "Board.hh"
#include <map>
#include <iostream>
#include <string>
#include <vector>

Board &Board::Instance()
{
  static Board instance;

  return instance;
}

void Board::InitializeBoard()
{
  squaresMap = std::map<Coordinate, Square>();

  for (int row = 1; row < 9; row++)
  {
    for (int column = 1; column < 9; column++)
    {
      std::pair<Coordinate, Square> squareCoordPair(Coordinate(column, row), Square());
      squaresMap.insert(squareCoordPair);
    }
  }
}

// TODO make this method const
void Board::printBoard(const bool &simplified)
{
  std::string top = (simplified) ? "---------------------------------" : "╔═══╤═══╤═══╤═══╤═══╤═══╤═══╤═══╗";
  std::string middle = (simplified) ? "|---|---|---|---|---|---|---|---|" : "╟───┼───┼───┼───┼───┼───┼───┼───╢";
  std::string bottom = (simplified) ? "---------------------------------" : "╚═══╧═══╧═══╧═══╧═══╧═══╧═══╧═══╝";
  std::string border = (simplified) ? "|" : "║";
  std::string separator = (simplified) ? "|" : "│";
  std::cout << "\n   " << top << "\n";
  for (int row = 8; row > 0; row--)
  {
    std::cout << " " << row << " " << border << " ";
    for (int column = 1; column < 9; column++)
    {
      // Have to use iterator to make method const
      std::map<Coordinate, Square>::iterator squareIterator(squaresMap.find(Coordinate(column, row)));
      std::cout << squareIterator->second.toString(simplified);
      // Slightly inefficient but makes the code cleaner
      if (column != 8)
        std::cout << " " << separator << " ";
      else
        std::cout << " " << border;
    }
    if (row != 1)
      std::cout << "\n   " << middle << "\n";
    else
      std::cout << "\n   " << bottom << "\n";
  }
  std::cout << "     a   b   c   d   e   f   g   h\n\n";
}

// TODO make this method const
void Board::printBoardReversed(const bool &simplified)
{
  std::string top = (simplified) ? "---------------------------------" : "╔═══╤═══╤═══╤═══╤═══╤═══╤═══╤═══╗";
  std::string middle = (simplified) ? "|---|---|---|---|---|---|---|---|" : "╟───┼───┼───┼───┼───┼───┼───┼───╢";
  std::string bottom = (simplified) ? "---------------------------------" : "╚═══╧═══╧═══╧═══╧═══╧═══╧═══╧═══╝";
  std::string border = (simplified) ? "|" : "║";
  std::string separator = (simplified) ? "|" : "│";
  std::cout << "\n   " << top << "\n";
  for (int row = 1; row < 9; row++)
  {
    std::cout << " " << row << " " << border << " ";
    for (int column = 8; column > 0; column--)
    {
      // Have to use iterator to make method const
      std::map<Coordinate, Square>::iterator squareIterator(squaresMap.find(Coordinate(column, row)));
      std::cout << squareIterator->second.toString(simplified);
      // Slightly inefficient but makes the code cleaner
      if (column != 1)
        std::cout << " " << separator << " ";
      else
        std::cout << " " << border;
    }
    if (row != 8)
      std::cout << "\n   " << middle << "\n";
    else
      std::cout << "\n   " << bottom << "\n";
  }
  std::cout << "     h   g   f   e   d   c   b   a\n\n";
}
