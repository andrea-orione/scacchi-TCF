#include "Coordinate.hh"

const std::string Coordinate::literalChars = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

/**
 * The default constructor.
 *
 * Takes two int and assigns them to the x and y coordinates,
 * after checking if they respect the constraints.
 *
 * @param[in] newX the value between 1 and 8 (included) to assign to the x (column).
 * @param[in] newY the value between 1 and 8 (included) to assign to the y (row).
 */
Coordinate::Coordinate(int newX, int newY)
{
  if (newX < 1 || newX > 8)
    throw std::out_of_range("x value outside the board");
  if (newY < 1 || newY > 8)
    throw std::out_of_range("y value outside the board");

  this->x = newX;
  this->y = newY;
}

/**
 * The constructor from (`char`, `int`) representing the coordinates.
 *
 * Takes a char and an int and assigns them to the x and y coordinates,
 * after checking if they respect the constraints.
 *
 * @param[in] literalNewX the value to assign to the x (column)
 *   valid values are chars from `a` to `h` (included) corresponding to an int from 1 to 8.
 * @param[in] newY the value between 1 and 8 (included) to assign to the y (row).
 */
Coordinate::Coordinate(char literalNewX, int newY)
{
  if (newY < 1 || newY > 8)
    throw std::out_of_range("y value outside the board");

  int xIndex = literalChars.find(literalNewX);
  if (xIndex == std::string::npos)
    throw std::invalid_argument("x value not valid");

  this->x = xIndex + 1;
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
Coordinate::Coordinate(std::string_view literalExpression)
{
  if (literalExpression.length() != 2)
    throw std::invalid_argument("Non valid literal expression");

  int newY = literalExpression[1] - '0';
  if (newY < 1 || newY > 8)
    throw std::out_of_range("y value outside the board");

  char literalNewX = literalExpression[0];
  int xIndex = literalChars.find(literalNewX);
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
 * The x setter.
 *
 * @param[in] newX an int from 1 to 8 (included) to assign to the x (column).
 *
 * @return a reference to the object, for cascaded member function calls.
 */
Coordinate &Coordinate::setX(int newX)
{
  if (newX < 1 || newX > 8)
    throw std::out_of_range("x value outside the board");

  this->x = newX;

  return *this;
}

/**
 * The y setter.
 *
 * @param[in] newY an int from 1 to 8 (included) to assign to the y (row).
 * @return a reference to the object, for cascaded member function calls.
 */
Coordinate &Coordinate::setY(int newY)
{
  if (newY < 1 || newY > 8)
    throw std::out_of_range("y value outside the board");

  this->y = newY;

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
Coordinate &Coordinate::operator+(const Movement &movement)
{
  int newX = x + movement.getX();
  int newY = y + movement.getY();

  if (newX < 1 || newX > 8)
    throw std::out_of_range("New Coordinate's x value outside the board");
  if (newY < 1 || newY > 8)
    throw std::out_of_range("New Coordinate's y value outside the board");

  this->x = newX;
  this->y = newY;

  return *this;
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
  int newX = x + movement.getX();
  int newY = y + movement.getY();

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
int Coordinate::squaredDistance(const Coordinate other) const
{
  return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
}

/**
 * Return the string representing the coordinate in a `char``int` format.
 *
 * @return the above described string.
 */
std::string Coordinate::toString() const
{
  return (literalChars[x - 1] + std::to_string(y));
}
