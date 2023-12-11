#include "Queen.hh"

Queen::Queen(PieceColor pColor, Coordinate pPosition)
{
  color = pColor;
  position = pPosition;
  switch (color)
  {
  case PieceColor::WHITE:
    character = "♛";
    literalCharacter = 'Q';
    break;
  case PieceColor::BLACK:
    character = "♕";
    literalCharacter = 'q';
    break;
  default:
    break;
  }
}

std::string Queen::toString(bool literal) const
{
  if (literal)
    return std::string(1, literalCharacter);
  return character;
}
