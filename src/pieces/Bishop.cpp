#include "Bishop.hh"

Bishop::Bishop(PieceColor pColor): color(pColor)
{
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
  if (literal) return std::to_string(literalCharacter);
  return character;
}

std::vector<Coordinate> Bishop::listValidCoordinate() const
{
  return std::vector<Coordinate>();
}