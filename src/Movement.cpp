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

/**
 * Operator `<` overloading.
 *
 * A movement is considered bigger than the other if it has a bigger y.
 * If two movements have the same y the one with the bigger x is considered bigger
 */
bool operator<(Movement left, Movement right)
{
  return (left.GetY() < right.GetY()) || ((left.GetY() == right.GetY()) && (left.GetX() < right.GetX()));
}

/**
 * Operator `>` overloading.
 *
 * A movement is considered smaller than the other if it has a smaller y.
 * If two movements have the same y the one with the smaller x is considered smaller
 */
bool operator>(Movement left, Movement right)
{
  return (left.GetY() > right.GetY()) || ((left.GetY() == right.GetY()) && (left.GetX() > right.GetX()));
}

/**
 * Operator `==` overloading.
 *
 * Two movements are considered equals if they have both the same x and the same y
 */
bool operator==(Movement left, Movement right) { return (left.GetX() == right.GetX() && left.GetY() == right.GetY()); }

/**
 * Operator `!=` overloading.
 */
bool operator!=(Movement left, Movement right) { return !(left == right); }

/**
 * Operator `<=` overloading.
 */
bool operator<=(Movement left, Movement right) { return !(left > right); }

/**
 * Operator `>=` overloading.
 */
bool operator>=(Movement left, Movement right) { return !(left < right); }
