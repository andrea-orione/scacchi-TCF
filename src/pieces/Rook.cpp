#include "Rook.hh"

Rook::Rook(PieceColor pColor, Coordinate pPosition)
{
  color = pColor;
  position = pPosition;
  switch (color)
  {
  case PieceColor::WHITE:
    character = "♜";
    literalCharacter = 'R';
    break;
  case PieceColor::BLACK:
    character = "♖";
    literalCharacter = 'r';
    break;
  default:
    break;
  }
}

std::string Rook::toString(bool literal) const
{
  if (literal) return std::string(1, literalCharacter);
  return character;
}

std::vector<Coordinate> Rook::listValidCoordinate() const
{
    return std::vector<Coordinate>();
}
