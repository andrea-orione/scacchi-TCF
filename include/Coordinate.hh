#pragma once

#include <string>

class Coordinate
{
private:
  static const std::string literalChars;

  int x;
  int y;
public:
  Coordinate(int newX=1, int newY=1);
  Coordinate(char literalNewX, int newY);
  Coordinate(std::string literalNewX, int newY);
  Coordinate(std::string literalExpression);

  Coordinate &setX(int newX);
  Coordinate &setY(int newY);
  int getX() const;
  int getY() const;

  void print() const;
  std::string toString() const;

private:
  
};
