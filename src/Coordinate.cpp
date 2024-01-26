#include "Coordinate.hh"

#include <stdexcept>
#include <string_view>

constexpr std::string_view literalChars{"abcdefgh"};

/**
 * The default constructor.
 *
 * Takes two int and assigns them to the x and y coordinates,
 * after checking if they respect the constraints.
 *
 * @param[in] newX the value between 1 and 8 (included) to assign to the x (column).
 * @param[in] newY the value between 1 and 8 (included) to assign to the y (row).
 */
Coordinate::Coordinate(const int newX, const int newY)
{
  if (newX < 1 || newX > 8)
    throw std::out_of_range("x value outside the board");
  if (newY < 1 || newY > 8)
    throw std::out_of_range("y value outside the board");

  this->x = newX;
  this->y = newY;
}

/**
 * The constructor from `string_view` representing the coordinates.
 *
 * Checks if the `string_view` is of the form "xn", with x being a
 * `char` from 'a' to 'h' and n an int from 1 to 8.
 *
 * @param[in] literalExpression The aforementioned `string_view`.
 */
Coordinate::Coordinate(const std::string_view literalExpression)
{
  if (literalExpression.length() != 2)
    throw std::invalid_argument("Non valid literal expression");

  const int newY = literalExpression.at(1) - '0';
  if (newY < 1 || newY > 8)
    throw std::out_of_range("y value outside the board");

  const int xIndex = literalChars.find(literalExpression.at(0));
  if (xIndex == std::string::npos)
    throw std::invalid_argument("x value not valid");

  this->x = xIndex + 1;
  this->y = newY;
}

/**
 * The copy constructor.
 *
 * @param[in] newCoordinate the Coordinate to be copied
 */
Coordinate::Coordinate(const Coordinate &newCoordinate)
{
  this->x = newCoordinate.x;
  this->y = newCoordinate.y;
}

/**
 * The copy operator.
 *
 * @param[in] newCoordinate the Coordinate to be copied.
 */
Coordinate &Coordinate::operator=(const Coordinate &newCoordinate)
{
  // Check for self assignment
  if (this != &newCoordinate)
  {
    this->x = newCoordinate.x;
    this->y = newCoordinate.y;
  }

  return *this;
}

/**
 * Operator `<` overloading.
 */
bool Coordinate::operator<(const Coordinate &other) const
{
  return (y < other.y) || ((y == other.y) && (x < other.x));
}

/**
 * Operator `>` overloading.
 */
bool Coordinate::operator>(const Coordinate &other) const
{
  return (y > other.y) || ((y == other.y) && (x > other.x));
}

/**
 * Operator `==` overloading.
 */
bool Coordinate::operator==(const Coordinate &other) const
{
  return (x == other.x && y == other.y);
}
/**
 * Operator `!=` overloading.
 */
bool Coordinate::operator!=(const Coordinate &other) const
{
  return !(x == other.x && y == other.y);
}

/**
 * Operator `<=` overloading.
 */
bool Coordinate::operator<=(const Coordinate &other) const
{
  return !((y > other.y) || ((y == other.y) && (x > other.x)));
}

/**
 * Operator `>=` overloading.
 */
bool Coordinate::operator>=(const Coordinate &other) const
{
  return !((y < other.y) || ((y == other.y) && (x < other.x)));
}

/**
 * The sum operator, to get to new coordinates.
 *
 * It uses a `Movement` object to generate the new `Coordinate`,
 * after checking if such new `Coordinate` respects the constraints.
 *
 * @param[in] movement The movement to perform.
 * @return the new Coordinate.
 */
Coordinate Coordinate::operator+(const Movement &movement) const
{
  const int newX = x + movement.GetX();
  const int newY = y + movement.GetY();

  if (newX < 1 || newX > 8)
    throw std::out_of_range("New Coordinate's x value outside the board");
  if (newY < 1 || newY > 8)
    throw std::out_of_range("New Coordinate's y value outside the board");

  return Coordinate(newX, newY);
}

/**
 * The increment operator, to get to new coordinates.
 *
 * It uses a Movement object to generate the new Coordinate,
 * after checking if such new `Coordinate` respects the constraints.
 *
 * @param[in] movement The movement to perform.
 * @return the new Coordinate.
 */
Coordinate &Coordinate::operator+=(const Movement &movement)
{
  const int newX = x + movement.GetX();
  const int newY = y + movement.GetY();

  if (newX < 1 || newX > 8)
    throw std::out_of_range("New Coordinate's x value outside the board");
  if (newY < 1 || newY > 8)
    throw std::out_of_range("New Coordinate's y value outside the board");

  this->x = newX;
  this->y = newY;

  return *this;
}

/**
 * Function for getting the distance squared between to coordinates.
 *
 * To increase the performance, the square root is avoided, as it would
 * not be useful anyway.
 *
 * @param[in] other The other `Coordinate`.
 * @return The distance squared.
 */
int Coordinate::SquaredDistance(const Coordinate other) const
{
  return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
}
