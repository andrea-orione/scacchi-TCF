#include "Movement.hh"
#include <stdexcept>

/**
 * The default constructor.
 *
 * Take two int and assignes them to the x and y
 * after checking they respect the constrains.
 *
 * @param[in] newX the value between -7 and +7 (included) to assign to the x (column) movement.
 * @param[in] newY the value between -7 and +7 (included) to assign to the y (row) movement.
 */
Movement::Movement(int newX, int newY)
{
  if (newX < -7 || newX > 7)
    throw std::out_of_range("x value not valid");
  if (newY < -7 || newY > 7)
    throw std::out_of_range("y value not valid");

  x = newX;
  y = newY;
}

/**
 * The copy constructor.
 *
 * @param[in] newMovement the Movement to be copied
 */
Movement::Movement(const Movement &newMovement)
{
  x = newMovement.x;
  y = newMovement.y;
}

/**
 * The copy operator.
 *
 * @param[in] newMovement the Movement to be copied.
 */
Movement Movement::operator=(const Movement &newMovement)
{
  return Movement(newMovement.x, newMovement.y);
}

/**
 * The x setter.
 *
 * @param[in] newX an int from -7 to 7 (included) to assign to the x (column) movement.
 * @return a reference to the object, for cascaded member function calls.
 */
Movement &Movement::setX(int newX)
{
  if (newX < -7 || newX > 7)
    throw std::out_of_range("x value not valid");

  x = newX;

  return *this;
}

/**
 * The y setter.
 *
 * @param[in] newY an int from -7 to +7 (included) to assign to the y (row) movement.
 * @return a reference to the object, for cascaded member function calls.
 */
Movement &Movement::setY(int newY)
{
  if (newY < -7 || newY > 7)
    throw std::out_of_range("y value not valid");

  y = newY;

  return *this;
}

/**
 * The direction inverter.
 *
 * It multiplies both the x and y component by -1 inverting the direction of the movement.
 *
 * @return a reference to the object, for cascaded member function calls.
 */
Movement &Movement::invertDirection()
{
  x*=-1;
  y*=-1;
  return *this;
}

/**
 * The x getter.
 *
 * @return the value of the x.
 */
int Movement::getX() const
{
  return x;
}

/**
 * The y getter.
 *
 * @return the value of the y.
 */
int Movement::getY() const
{
  return y;
}

bool Movement::operator<(const Movement &other) const
{
  return (y < other.y) || ((y == other.y) && (x < other.x));
}

bool Movement::operator>(const Movement &other) const
{
  return (y > other.y) || ((y == other.y) && (x > other.x));
}

bool Movement::operator==(const Movement &other) const
{
  return (x == other.x && y == other.y);
}

bool Movement::operator<=(const Movement &other) const
{
  return !((y > other.y) || ((y == other.y) && (x > other.x)));
}

bool Movement::operator>=(const Movement &other) const
{
  return !((y < other.y) || ((y == other.y) && (x < other.x)));
}

/**
 * The multiplier operator.
 *
 * Return the movement scaled by the multiplier factor, if the result stays in the constrains.
 *
 * @param[in] multiplier the positive factor by which the movement will be scaled.
 * @return the scaled movement.
 */
Movement Movement::operator*(int multiplier) const
{
  if (multiplier < 1 || multiplier > 7)
    throw std::out_of_range("Multiplier out of range");

  int newX = x * multiplier;
  int newY = y * multiplier;

  if (newX < -7 || newX > 7)
    throw std::out_of_range("New Movement's x value not valid");
  if (newY < -7 || newY > 7)
    throw std::out_of_range("New Movement's y value not valid");

  return Movement(newX, newY);
}
