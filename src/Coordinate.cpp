#include "../include/Coordinate.hh"
#include <iostream>
#include <stdexcept>
#include <string>

const std::string Coordinate::literalChars = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

Coordinate::Coordinate(const int &newX, const int &newY) {
  if (newX < 1 || newX > 8) throw std::out_of_range("x value outside the board");
  if (newY < 1 || newY > 8) throw std::out_of_range("y value outside the board");
  x = newX;
  y = newY;
}

Coordinate::Coordinate(const char &literalNewX, const int &newY) {
  if (newY < 1 || newY > 8) throw std::out_of_range("y value outside the board");
  int xIndex = literalChars.find(literalNewX);
  if (xIndex == std::string::npos) throw std::invalid_argument("x value not valid");
  x = xIndex+1;
  y = newY;
}

Coordinate::Coordinate(const std::string &literalNewX, const int &newY) {
  if (newY < 1 || newY > 8) throw std::out_of_range("y value outside the board");
  if (literalNewX.length() != 1) throw std::invalid_argument("x value not valid");
  int xIndex = literalChars.find(literalNewX);
  if (xIndex == std::string::npos) throw std::invalid_argument("x value not valid");
  x = xIndex+1;
  y = newY;
}

Coordinate::Coordinate(const std::string &literalExpression) {
  if (literalExpression.length() != 2) throw std::invalid_argument("Non valid literal expression");
  int newY = std::stoi(literalExpression.substr(1,1));
  if (newY < 1 || newY > 8) throw std::out_of_range("y value outside the board");
  char literalNewX = literalExpression[0];
  int xIndex = literalChars.find(literalNewX);
  if (xIndex == std::string::npos) throw std::invalid_argument("x value not valid");
  x = xIndex+1;
  y = newY;
}

Coordinate::Coordinate(const Coordinate &newCoordinate) {
  x = newCoordinate.x;
  y = newCoordinate.y;
}

Coordinate Coordinate::operator=(const Coordinate &newCoordinate) {
  return Coordinate(newCoordinate.x, newCoordinate.y);
}

Coordinate &Coordinate::setX(const int &newX) {
  if (newX < 1 || newX > 8) throw std::out_of_range("x value outside the board");
  x = newX;
  return *this;
}

Coordinate &Coordinate::setY(const int &newY) {
  if (newY < 1 || newY > 8) throw std::out_of_range("y value outside the board");
  y = newY;
  return *this;
}

int Coordinate::getX() const {
  return x;
}

int Coordinate::getY() const {
  return y;
}

bool Coordinate::operator<(const Coordinate &other) const {
  return (y < other.y) || ((y == other.y) && (x < other.x));
}

bool Coordinate::operator>(const Coordinate &other) const {
  return (y > other.y) || ((y == other.y) && (x > other.x));
}

bool Coordinate::operator==(const Coordinate &other) const {
  return (x==other.x && y==other.y);
}

bool Coordinate::operator<=(const Coordinate &other) const {
  return !((y > other.y) || ((y == other.y) && (x > other.x)));
}

bool Coordinate::operator>=(const Coordinate &other) const {
  return !((y < other.y) || ((y == other.y) && (x < other.x)));
}

Coordinate Coordinate::operator+(const Movement &movement) const {
  int newX = x + movement.getX();
  int newY = y + movement.getY();
  if (newX < 1 || newX > 8) throw std::out_of_range("New Coordinate's x value outside the board");
  if (newY < 1 || newY > 8) throw std::out_of_range("New Coordinate's y value outside the board");
  return Coordinate(newX, newY);
}

void Coordinate::print() const {
  std::cout << literalChars[x-1] << y << std::endl;
}

std::string Coordinate::toString() const {
  return (literalChars[x-1] + std::to_string(y));
}
