#include "Knight.hh"

Knight::Knight(PieceColor pColor, Coordinate pPosition)
{
  color = pColor;
  position = pPosition;
  switch (color)
  {
  case PieceColor::WHITE:
    character = "♞";
    literalCharacter = 'N';
    break;
  case PieceColor::BLACK:
    character = "♘";
    literalCharacter = 'n';
    break;
  default:
    break;
  }
}

std::string Knight::toString(bool literal) const
{
  if (literal) return std::string(1, literalCharacter);
  return character;
}

std::vector<Coordinate> Knight::listValidCoordinate() const
{
    return std::vector<Coordinate>();
}
