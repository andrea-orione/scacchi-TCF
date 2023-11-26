#pragma once

//TODO Consider making the scaling factor unsigned, to remove condition checking. Consider that also 0 is not allowed.
//TODO Consider switching the * operator whith a traditional method `Movement scale(const int multiplier) const`. Just 'cause. Idk.
/**
 * The movement system on the board.
 *
 * It is just a pair of two integers constrained between -7 and +7 (included).
 * It is useful to implement the possible moves of each piece using the multiplication.
 * It is specifically designed to be added to a Coordinate object.
 */
class Movement
{
public:
  /**
   * The default constructor.
   * 
   * Take two int and assignes them to the x and y
   * after checking they respect the constrains.
   *
   * @param[in] newX the value between -7 and +7 (included) to assign to the x (column) movement.
   * @param[in] newY the value between -7 and +7 (included) to assign to the y (row) movement.
   */ 
  Movement(const int &newX=0, const int &newY=0);

  /**
   * The copy constructor.
   * 
   * @param[in] newMovement the Movement to be copied
   */
  Movement(const Movement &newMovement);

  /**
   * The copy operator.
   *
   * @param[in] newMovement the Movement to be copied.
   */
  Movement operator = (const Movement &newMovement);
  
  /**
   * The x setter.
   *
   * @param[in] newX an int from -7 to 7 (included) to assign to the x (column) movement.
   * @return a reference to the object, for cascaded member function calls.
   */
  Movement &setX(const int &newX);
  
  /**
   * The y setter.
   *
   * @param[in] newY an int from -7 to +7 (included) to assign to the y (row) movement.
   * @return a reference to the object, for cascaded member function calls.
   */
  Movement &setY(const int &newY);

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

  // Used in containers, such as vectors. (< and == should have been enough but you never know)
  bool operator < (const Movement &other) const;
  bool operator > (const Movement &other) const;
  bool operator == (const Movement &other) const;
  bool operator <= (const Movement &other) const;
  bool operator >= (const Movement &other) const;

  /**
   * The multiplier operator.
   *
   * Return the movement scaled by the multiplier factor, if the result stays in the constrains.
   * 
   * @param[in] multiplier the positive factor by which the movement will be scaled.
   * @return the scaled movement.
   */
  Movement operator * (const int &multiplier) const;

private:
  int x;
  int y;
};
