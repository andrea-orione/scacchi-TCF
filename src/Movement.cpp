#include "Movement.hh"

#include <stdexcept>

/**
 * The default constructor.
 *
 * Takes two int and assigns them to the x and y coordinates,
 * after checking if they respect the constraints.
 *
 * @param[in] newX the value between -7 and +7 (included) to assign to the x (column) movement.
 * @param[in] newY the value between -7 and +7 (included) to assign to the y (row) movement.
 */
Movement::Movement(const int newX, const int newY)
{
  if (newX < -7 || newX > 7)
    throw std::out_of_range("x value not valid");
  if (newY < -7 || newY > 7)
    throw std::out_of_range("y value not valid");

  this->x = newX;
  this->y = newY;
}

/**
 * The copy constructor.
 *
 * @param[in] newMovement the Movement to be copied
 */
Movement::Movement(const Movement &newMovement)
{
  this->x = newMovement.x;
  this->y = newMovement.y;
}

/**
 * The copy operator.
 *
 * @param[in] newMovement the Movement to be copied.
 */
Movement &Movement::operator=(const Movement &newMovement)
{
  // Check for self assignment
  if (this != &newMovement)
  {
    this->x = newMovement.x;
    this->y = newMovement.y;
  }
  return *this;
}

/**
 * Operator `<` overloading.
 */
bool Movement::operator<(const Movement &other) const
{
  return (y < other.y) || ((y == other.y) && (x < other.x));
}

/**
 * Operator `>` overloading.
 */
bool Movement::operator>(const Movement &other) const
{
  return (y > other.y) || ((y == other.y) && (x > other.x));
}

/**
 * Operator `==` overloading.
 */
bool Movement::operator==(const Movement &other) const
{
  return (x == other.x && y == other.y);
}

/**
 * Operator `!=` overloading.
 */
bool Movement::operator!=(const Movement &other) const
{
  return !(x == other.x && y == other.y);
}

/**
 * Operator `<=` overloading.
 */
bool Movement::operator<=(const Movement &other) const
{
  return !((y > other.y) || ((y == other.y) && (x > other.x)));
}

/**
 * Operator `>=` overloading.
 */
bool Movement::operator>=(const Movement &other) const
{
  return !((y < other.y) || ((y == other.y) && (x < other.x)));
}

/**
 * Operator `*` overloading.
 *
 * Return the movement scaled by the multiplier factor, if the result respects the constraints.
 *
 * @param[in] multiplier the positive factor by which the movement will be scaled.
 * @return the scaled movement.
 */
Movement Movement::operator*(const int multiplier) const
{
  if (multiplier < 1 || multiplier > 7)
    throw std::out_of_range("Multiplier out of range");

  const int newX = x * multiplier;
  const int newY = y * multiplier;

  if (newX < -7 || newX > 7)
    throw std::out_of_range("New Movement's x value not valid");
  if (newY < -7 || newY > 7)
    throw std::out_of_range("New Movement's y value not valid");

  return Movement(newX, newY);
}
