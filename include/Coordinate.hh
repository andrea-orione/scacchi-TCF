#pragma once

#include <string>

//TODO Delete DEPRECATED methods
/**
 * The coordinate system on the board.
 *
 * It is just a pair of two integers constrained between 1 and 8 (included).
 */
class Coordinate
{
public:
  /**
   * The default constructor.
   * 
   * Take two int and assignes them to the x and y
   * after checking they respect the constrains.
   *
   * @param[in] newX the value between 1 and 8 (included) to assign to the x (column).
   * @param[in] newY the value between 1 and 8 (included) to assign to the y (row).
   */
  Coordinate(int newX=1, int newY=1);
  
  /**
   * Take a char and an int and assignes them to the x and y
   * after checking they respect the constrains.
   *
   * @param[in] literalNewX the value to assign to the x (column)
   *   valid values are chars from `a` to `h` (included) corresponding to an int from 1 to 8.
   * @param[in] newY the value between 1 and 8 (included) to assign to the y (row).
   */
  Coordinate(char literalNewX, int newY);

  /**
   * Take a std::string and an int and assignes them to the x and y
   * after checking they respect the constrains.
   *
   * @param[in] literalNewX the value to assign to the x (column)
   *   valid values are chars from `a` to `h` (included) corresponding to an int from 1 to 8.
   * @param[in] newY the value between 1 and 8 (included) to assign to the y (row).
   */
  Coordinate(std::string literalNewX, int newY);

  /**
   * Take a string representing the coordinate with a char and an int.
   *
   * @param[in] literalEspression the value to instantiate
   *   valid values are 2 chars long string containing
   *   a char from `a` to `h` (included) corresponding to an int from 1 to 8 for the x (column)
   *   and an int between 1 to 8 (included) for the y (row).
   */
  Coordinate(std::string literalExpression);

  /**
   * The x setter.
   *
   * @param[in] newX an int from 1 to 8 (included) to assign to the x (column).
   * @return a reference to the object, for cascaded member function calls.
   */
  Coordinate &setX(int newX);
  
  /**
   * The y setter.
   *
   * @param[in] newY an int from 1 to 8 (included) to assign to the x (row).
   * @return a reference to the object, for cascaded member function calls.
   */
  Coordinate &setY(int newY);

  /**
   * The x getter.
   *
   * @return the value of the x.
   */
  int getX() const;

  /**
   * The y getter.
   *
   * @return the value of the y.
   */
  int getY() const;

  bool operator < (const Coordinate other) const;
  bool operator > (const Coordinate other) const;
  bool operator == (const Coordinate other) const;
  bool operator <= (const Coordinate other) const;
  bool operator >= (const Coordinate other) const;

  /**
   * DEPRECATED, ONLY FOR TESTING. Print the coordinate in a `char``int` format to the screen.
   * 
   * Use toString instead
   */
  void print() const;
  
  /**
   * Return the string representing the coordinate in a `char``int` format.
   *
   * @return the above described string.
   */
  std::string toString() const;

private:
  static const std::string literalChars;
  int x;
  int y;
};
