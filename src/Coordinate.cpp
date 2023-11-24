#include "../include/Coordinate.hh"
#include <iostream>
#include <stdexcept>
#include <string>

const std::string Coordinate::literalChars = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

Coordinate::Coordinate():
  x(1),
  y(1) {}

Coordinate::Coordinate(int newX, int newY) {
  if (newX < 1 || newX > 8) throw std::out_of_range("x value outside the board");
  if (newY < 1 || newY > 8) throw std::out_of_range("y value outside the board");
  x = newX;
  y = newY;
}

Coordinate::Coordinate(const char literalNewX, int newY) {
  if (newY < 1 || newY > 8) throw std::out_of_range("y value outside the board");
  int xIndex = literalChars.find(literalNewX);
  if (xIndex == std::string::npos) throw std::invalid_argument("x value not valid");
  x = xIndex+1;
  y = newY;
}

Coordinate::Coordinate(std::string literalNewX, int newY) {
  if (newY < 1 || newY > 8) throw std::out_of_range("y value outside the board");
  if (literalNewX.length() != 1) throw std::invalid_argument("x value not valid");
  int xIndex = literalChars.find(literalNewX);
  if (xIndex == std::string::npos) throw std::invalid_argument("x value not valid");
  x = xIndex+1;
  y = newY;
}

Coordinate::Coordinate(std::string literalExpression) {
  if (literalExpression.length() != 2) throw std::invalid_argument("Non valid literal expression");
  int newY = std::stoi(literalExpression.substr(1,1));
  if (newY < 1 || newY > 8) throw std::out_of_range("y value outside the board");
  char literalNewX = literalExpression[0];
  int xIndex = literalChars.find(literalNewX);
  if (xIndex == std::string::npos) throw std::invalid_argument("x value not valid");
  x = xIndex+1;
  y = newY;
}

Coordinate &Coordinate::setX(int newX) {
  if (newX > 8 || newX < 1) throw std::out_of_range("x value outside the board");
  x = newX;
  return *this;
}

Coordinate &Coordinate::setY(int newY) {
  if (newY > 8 || newY < 1) throw std::out_of_range("y value outside the board");
  y = newY;
  return *this;
}

int Coordinate::getX() const {
  return x;
}

int Coordinate::getY() const {
  return y;
}

void Coordinate::print() const {
  std::cout << literalChars[x-1] << y << std::endl;
}

std::string Coordinate::toString() const {
  return (literalChars[x-1] + std::to_string(y));
}
