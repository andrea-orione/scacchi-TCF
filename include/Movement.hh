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

  inline int GetX() const { return x; }
  inline int GetY() const { return y; }

  Movement operator*(int multiplier) const;

private:
  int x;
  int y;
};

bool operator<(Movement left, Movement right);
bool operator>(Movement left, Movement right);
bool operator==(Movement left, Movement right);
bool operator!=(Movement left, Movement right);
bool operator<=(Movement left, Movement right);
bool operator>=(Movement left, Movement right);
