#pragma once

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
  Movement(int newX = 0, int newY = 0);
  Movement(const Movement &newMovement);
  Movement &operator=(const Movement &newMovement);

  Movement &setX(int newX);
  Movement &setY(int newY);
  Movement &invertDirection();
  int getX() const;
  int getY() const;

  // Used in containers, such as vectors. (< and == should have been enough but you never know)
  bool operator<(const Movement &other) const;
  bool operator>(const Movement &other) const;
  bool operator==(const Movement &other) const;
  bool operator<=(const Movement &other) const;
  bool operator>=(const Movement &other) const;

  Movement operator*(int multiplier) const;

private:
  int x;
  int y;
};
