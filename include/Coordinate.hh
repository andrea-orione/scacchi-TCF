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
  Coordinate(int newX = 1, int newY = 1);
  Coordinate(std::string_view literalExpression);
  ~Coordinate() = default;

  Coordinate(const Coordinate &newCoordinate);
  Coordinate &operator=(const Coordinate &newCoordinate);

  int GetX() const { return x; }
  int GetY() const { return y; }

  bool operator<(const Coordinate &other) const;
  bool operator>(const Coordinate &other) const;
  bool operator==(const Coordinate &other) const;
  bool operator!=(const Coordinate &other) const;
  bool operator<=(const Coordinate &other) const;
  bool operator>=(const Coordinate &other) const;

  Coordinate operator+(const Movement &movement) const;
  Coordinate &operator+=(const Movement &movement);

  int SquaredDistance(Coordinate other) const;

private:
  int x;
  int y;
};
