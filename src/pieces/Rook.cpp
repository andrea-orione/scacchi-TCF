#include "Rook.hh"

Rook::Rook(PieceColor pColor, Coordinate pPosition)
{
  color = pColor;
  position = pPosition;
  switch (color)
  {
  case PieceColor::WHITE:
    character = "♜";
    break;
  case PieceColor::BLACK:
    character = "♖";
    break;
  default:
    break;
  }

  switch (color)
  {
  case PieceColor::WHITE:
    literalCharacter = 'R';
    break;
  case PieceColor::BLACK:
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