#pragma once

#include <string>

class Coordinates
{
private:
  static const std::string literalChars;

  int x;
  int y;
public:
  Coordinates(int newX, int newY);
  Coordinates(char literalNewX, int newY);
  Coordinates(std::string literalNewX, int newY);
  Coordinates(std::string literalExpression);

  Coordinates &setX(int newX);
  Coordinates &setY(int newY);
  int getX() const;
  int getY() const;


private:
  
};
