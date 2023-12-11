#include "Bishop.hh"

#include "Movement.hh"

Bishop::Bishop(PieceColor pColor, Coordinate pPosition)
{
  color = pColor;
  position = pPosition;
  switch (color)
  {
  case PieceColor::WHITE:
    character = "♝";
    literalCharacter = 'B';
    break;
  case PieceColor::BLACK:
    character = "♗";
    literalCharacter = 'b';
    break;
  default:
    break;
  }
}

std::string Bishop::toString(bool literal) const
{
  if (literal)
    return std::string(1, literalCharacter);
  return character;
}

bool Bishop::isMoveValid(const Coordinate &startingPosition, const Coordinate &endingPosition) const
{
  int xDistance = endingPosition.getX() - startingPosition.getX();
  int yDistance = endingPosition.getY() - startingPosition.getY();

  // geometric check
  if (abs(xDistance) != abs(yDistance))
    return false;

  // determine diagonal
  Movement base_move;
  if (xDistance - yDistance != 0)
  {
    if (xDistance > yDistance)
      base_move = Movement(1, -1);
    else
      base_move = Movement(-1, 1);
  }
  else
  {
    if (xDistance > 0 && yDistance > 0)
      base_move = Movement(1, 1);
    else
      base_move = Movement(-1, -1);
  }
}