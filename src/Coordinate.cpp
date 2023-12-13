#include "Coordinate.hh"

const std::string Coordinate::literalChars = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

/**
 * The default constructor.
 *
 * Take two int and assignes them to the x and y
 * after checking they respect the constrains.
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

  x = newX;
  y = newY;
}

/**
 * Take a char and an int and assignes them to the x and y
 * after checking they respect the constrains.
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

  x = xIndex + 1;
  y = newY;
}

/**
 * Take a std::string and an int and assignes them to the x and y
 * after checking they respect the constrains.
 *
 * @param[in] literalNewX the value to assign to the x (column)
 *   valid values are chars from `a` to `h` (included) corresponding to an int from 1 to 8.
 * @param[in] newY the value between 1 and 8 (included) to assign to the y (row).
 */
Coordinate::Coordinate(std::string literalNewX, int newY)
{
  if (newY < 1 || newY > 8)
    throw std::out_of_range("y value outside the board");
  if (literalNewX.length() != 1)
    throw std::invalid_argument("x value not valid");

  int xIndex = literalChars.find(literalNewX);
  if (xIndex == std::string::npos)
    throw std::invalid_argument("x value not valid");

  x = xIndex + 1;
  y = newY;
}

/**
 * Take a string representing the coordinate with a char and an int.
 *
 * @param[in] literalEspression the value to instantiate
 *   valid values are 2 chars long string containing
 *   a char from `a` to `h` (included) corresponding to an int from 1 to 8 for the x (column)
 *   and an int between 1 to 8 (included) for the y (row).
 */
Coordinate::Coordinate(std::string literalExpression)
{
  if (literalExpression.length() != 2)
    throw std::invalid_argument("Non valid literal expression");

  int newY = std::stoi(literalExpression.substr(1, 1));
  if (newY < 1 || newY > 8)
    throw std::out_of_range("y value outside the board");

  char literalNewX = literalExpression[0];
  int xIndex = literalChars.find(literalNewX);
  if (xIndex == std::string::npos)
    throw std::invalid_argument("x value not valid");

  x = xIndex + 1;
  y = newY;
}

/**
 * Take an `std::string` representing the coordinate with a char and an int.
 *
 * @param[in] literalEspression the value to instantiate
 *   valid values are 2 chars long string containing
 *   a char from `a` to `h` (included) corresponding to an int from 1 to 8 for the x (column)
 *   and an int between 1 to 8 (included) for the y (row).
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

  x = xIndex + 1;
  y = newY;
}

/**
 * The copy constructor.
 *
 * @param[in] newCoordinate the Coordinate to be copied
 */
Coordinate::Coordinate(const Coordinate &newCoordinate)
{
  x = newCoordinate.x;
  y = newCoordinate.y;
}

/**
 * The copy operator.
 *
 * @param[in] newCoordinate the Coordinate to be copied.
 */
Coordinate Coordinate::operator=(const Coordinate &newCoordinate)
{
  return Coordinate(newCoordinate.x, newCoordinate.y);
}

/**
 * The x setter.
 *
 * @param[in] newX an int from 1 to 8 (included) to assign to the x (column).
 * @return a reference to the object, for cascaded member function calls.
 */
Coordinate &Coordinate::setX(int newX)
{
  if (newX < 1 || newX > 8)
    throw std::out_of_range("x value outside the board");

  x = newX;

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

  y = newY;

  return *this;
}

/**
 * The x getter.
 *
 * @return the value of the x.
 */
int Coordinate::getX() const
{
  return x;
}

/**
 * The y getter.
 *
 * @return the value of the y.
 */
int Coordinate::getY() const
{
  return y;
}

bool Coordinate::operator<(const Coordinate &other) const
{
  return (y < other.y) || ((y == other.y) && (x < other.x));
}

bool Coordinate::operator>(const Coordinate &other) const
{
  return (y > other.y) || ((y == other.y) && (x > other.x));
}

bool Coordinate::operator==(const Coordinate &other) const
{
  return (x == other.x && y == other.y);
}

bool Coordinate::operator<=(const Coordinate &other) const
{
  return !((y > other.y) || ((y == other.y) && (x > other.x)));
}

bool Coordinate::operator>=(const Coordinate &other) const
{
  return !((y < other.y) || ((y == other.y) && (x < other.x)));
}

/**
 * The sum operator, to get to new coordinates.
 *
 * It uses a Movement object to generate the new Coordinate, after checking that respects the constrains.
 *
 * @param[in] movement the indication of the movement.
 * @return the new Coordinate.
 */
Coordinate Coordinate::operator+(const Movement &movement) const
{
  int newX = x + movement.getX();
  int newY = y + movement.getY();

  if (newX < 1 || newX > 8)
    throw std::out_of_range("New Coordinate's x value outside the board");
  if (newY < 1 || newY > 8)
    throw std::out_of_range("New Coordinate's y value outside the board");

  return Coordinate(newX, newY);
}

/**
 * The increment operator, to get to new coordinates.
 *
 * It uses a Movement object to generate the new Coordinate, after checking that respects the constrains.
 *
 * @param[in] movement the indication of the movement.
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

  x = newX;
  y = newY;

  return *this;
}

/**
 * Return the distance squared.
 *
 * It doesn't return the square root to increase performance.
 *
 * @param[in] other the other coordinate between which the distance
 *   has to be calculated
 * @return the distance squared.
 */
int Coordinate::squaredDistance(const Coordinate &other) const
{
  return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
}

/**
 * DEPRECATED, ONLY FOR TESTING. Print the coordinate in a `char``int` format to the screen.
 *
 * Use toString instead
 */
void Coordinate::print() const
{
  std::cout << literalChars[x - 1] << y << std::endl;
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
