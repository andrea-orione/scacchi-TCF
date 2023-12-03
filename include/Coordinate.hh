#pragma once

#include <string>
#include <iostream>
#include <stdexcept>

#include "Movement.hh"

// TODO Delete DEPRECATED methods
// TODO Consider switching the + operator whith a traditional method `Movement add(const Movement movement) const`. Just 'cause. Idk.
/**
 * The coordinate system on the board.
 *
 * It is just a pair of two integers constrained between 1 and 8 (included).
 */
class Coordinate
{
public:
  Coordinate(int newX = 1, int newY = 1);
  Coordinate(char literalNewX, int newY);
  Coordinate(std::string literalNewX, int newY);
  Coordinate(std::string literalExpression);
  Coordinate(const Coordinate &newCoordinate);
  Coordinate operator=(const Coordinate &newCoordinate);

  Coordinate &setX(int newX);
  Coordinate &setY(int newY);
  int getX() const;
  int getY() const;

  // Used in containers, such as maps. (< and == should have been enough but you never know)
  bool operator<(const Coordinate &other) const;
  bool operator>(const Coordinate &other) const;
  bool operator==(const Coordinate &other) const;
  bool operator<=(const Coordinate &other) const;
  bool operator>=(const Coordinate &other) const;

  Coordinate operator+(const Movement &movement) const;

  int squaredDistance(const Coordinate &other) const;

  void print() const;  // DEPRECATED. USE `toString` INSTEAD
  std::string toString() const;

private:
  static const std::string literalChars;
  int x;
  int y;
};
