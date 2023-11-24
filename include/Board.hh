#pragma once

#include "Coordinate.hh"
#include "Square.hh"
#include <map>
#include <vector>

class Board
{
private:
  std::vector<Square> squaresVector;
  std::map<Coordinate, Square> squaresMap;


public:
  Board();
  Board(Board &&) = default;
  Board(const Board &) = default;
  Board &operator=(Board &&) = default;
  Board &operator=(const Board &) = default;

  void printBoard();

};
