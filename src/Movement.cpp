#include "../include/Movement.hh"
#include <stdexcept>

Movement::Movement(const int &newX, const int &newY) {
  if (newX < -7 || newX > 7) throw std::out_of_range("x value not valid");
  if (newY < -7 || newY > 7) throw std::out_of_range("y value not valid");
  x = newX;
  y = newY;
}

Movement::Movement(const Movement &newMovement) {
  x = newMovement.x;
  y = newMovement.y;
}

Movement Movement::operator=(const Movement &newMovement) {
  return Movement(newMovement.x, newMovement.y);
}

Movement &Movement::setX(const int &newX) {
  if (newX < -7 || newX > 7) throw std::out_of_range("x value not valid");
  x = newX;
  return *this;
}

Movement &Movement::setY(const int &newY) {
  if (newY < -7 || newY > 7) throw std::out_of_range("y value not valid");
  y = newY;
  return *this;
}

int Movement::getX() const {
  return x;
}

int Movement::getY() const {
  return y;
}

bool Movement::operator<(const Movement &other) const {
  return (y < other.y) || ((y == other.y) && (x < other.x));
}

bool Movement::operator>(const Movement &other) const {
  return (y > other.y) || ((y == other.y) && (x > other.x));
}

bool Movement::operator==(const Movement &other) const {
  return (x==other.x && y==other.y);
}

bool Movement::operator<=(const Movement &other) const {
  return !((y > other.y) || ((y == other.y) && (x > other.x)));
}

bool Movement::operator>=(const Movement &other) const {
  return !((y < other.y) || ((y == other.y) && (x < other.x)));
}

Movement Movement::operator*(const int &multiplier) const {
  if (multiplier < 1 || multiplier > 7) throw std::out_of_range("Multiplier out of range");
  int newX = x * multiplier;
  int newY = y * multiplier;
  if (newX < -7 || newX > 7) throw std::out_of_range("New Movement's x value not valid");
  if (newY < -7 || newY > 7) throw std::out_of_range("New Movement's y value not valid");
  return Movement(newX, newY);
}
