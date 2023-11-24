#include "../include/Coordinates.hh"
#include <iostream>
#include <stdexcept>
#include <string>

const std::string Coordinates::literalChars = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

Coordinates::Coordinates():
  x(1),
  y(1)
{}

Coordinates::Coordinates(int newX, int newY)
{
  if (newX < 1 || newX > 8) throw std::out_of_range("x value outside the board");
  if (newY < 1 || newY > 8) throw std::out_of_range("y value outside the board");
  x = newX;
  y = newY;
}

Coordinates::Coordinates(const char literalNewX, int newY)
{
  if (newY < 1 || newY > 8) throw std::out_of_range("y value outside the board");
  int xIndex = literalChars.find(literalNewX);
  if (xIndex == std::string::npos) throw std::invalid_argument("x value not valid");
  x = xIndex+1;
  y = newY;
}

Coordinates::Coordinates(std::string literalNewX, int newY)
{
  if (newY < 1 || newY > 8) throw std::out_of_range("y value outside the board");
  if (literalNewX.length() != 1) throw std::invalid_argument("x value not valid");
  int xIndex = literalChars.find(literalNewX);
  if (xIndex == std::string::npos) throw std::invalid_argument("x value not valid");
  x = xIndex+1;
  y = newY;
}

Coordinates::Coordinates(std::string literalExpression)
{
  if (literalExpression.length() != 2) throw std::invalid_argument("Non valid literal expression");
  

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

void Coordinates::print() const
{
  std::cout << literalChars[x-1] << y << std::endl;
}

std::string Coordinates::toString() const
{
  return (literalChars[x-1] + std::to_string(y));
}
