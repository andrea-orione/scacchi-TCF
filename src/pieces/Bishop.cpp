#include "Bishop.hh"

Bishop::Bishop(PieceColor pColor, Coordinate pPosition)
{
  color = pColor;
  position = pPosition;
  switch (color)
  {
  case PieceColor::WHITE:
    character = "♝";
    break;
  case PieceColor::BLACK:
    character = "♗";
    break;
  default:
    break;
  }

  switch (color)
  {
  case PieceColor::WHITE:
    literalCharacter = 'B';
    break;
  case PieceColor::BLACK:
    literalCharacter = 'b';
    break;
  default:
    break;
  }
}

std::string Bishop::toString(bool literal) const
{
  if (literal) return std::string(1, literalCharacter);
  return character;
}

std::vector<Coordinate> Bishop::listValidCoordinate() const
{
  return std::vector<Coordinate>();
}