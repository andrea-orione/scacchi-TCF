#include "Knight.hh"

Knight::Knight(PieceColor pColor)
{
  color = pColor;
  switch (color)
  {
  case PieceColor::WHITE:
    character = "♞";
    break;
  case PieceColor::BLACK:
    character = "♘";
    break;
  default:
    break;
  }

  switch (color)
  {
  case PieceColor::WHITE:
    literalCharacter = 'N';
    break;
  case PieceColor::BLACK:
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