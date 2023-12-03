#include "King.hh"

King::King(PieceColor pColor, Coordinate pPosition)
{
  color = pColor;
  position = pPosition;
  switch (color)
  {
  case PieceColor::WHITE:
    character = "♚";
    literalCharacter = 'K';
    break;
  case PieceColor::BLACK:
    character = "♔";
    literalCharacter = 'k';
    break;
  default:
    break;
  }
}

std::string King::toString(bool literal) const
{
  if (literal) return std::string(1, literalCharacter);
  return character;
}

std::vector<Coordinate> King::listValidCoordinate() const
{
  return std::vector<Coordinate>();
}
