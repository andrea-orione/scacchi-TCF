#pragma once

#include "Square.hh"
#include <vector>

class Board
{
private:
  std::vector<Square> squaresVector;

public:
  Board();
  Board(Board &&) = default;
  Board(const Board &) = default;
  Board &operator=(Board &&) = default;
  Board &operator=(const Board &) = default;

  void printBoard();

};
