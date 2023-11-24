#include "../include/Coordinates.hh"
#include <stdexcept>
#include <string>

const std::string Coordinates::literalChars = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

Coordinates::Coordinates(int newX, int newY)
{
  if (newX > 8 || newY < 1) throw std::out_of_range("x value outside the board");
  if (newY > 8 || newY < 1) throw std::out_of_range("y value outside the board");
  x = newX;
  y = newY;
}

Coordinates::Coordinates(const char literalNewX, int newY)
{
}

Coordinates::Coordinates(std::string literalNewX, int newY)
{

}

Coordinates::Coordinates(std::string literalExpression)
{

}

Coordinates &Coordinates::setX(int newX)
{
  if (newX > 8 || newX < 1) throw std::out_of_range("x value outside the board");
  x = newX;
  return *this;
}

Coordinates &Coordinates::setY(int newY)
{
  if (newY > 8 || newY < 1) throw std::out_of_range("y value outside the board");
  y = newY;
  return *this;
}

int Coordinates::getX() const
{
  return x;
}

int Coordinates::getY() const
{
  return y;
}
