#pragma once

#include <string_view>

#include "Movement.hh"

/**
 * The coordinate system on the board.
 *
 * It is just a pair of two integers constrained between 1 and 8 (included).
 */
class Coordinate
{
public:
  Coordinate(int newX=1, int newY=1);
  Coordinate(std::string_view literalExpression);

  inline int GetX() const { return x; }
  inline int GetY() const { return y; }

  Coordinate operator+(Movement movement) const;
  Coordinate &operator+=(Movement movement);

private:
  int x;
  int y;
};

bool operator<(Coordinate left, Coordinate right);
bool operator>(Coordinate left, Coordinate right);
bool operator==(Coordinate left, Coordinate right);
bool operator!=(Coordinate left, Coordinate right);
bool operator<=(Coordinate left, Coordinate right);
bool operator>=(Coordinate left, Coordinate right);

int SquaredDistance(Coordinate left, Coordinate right);
