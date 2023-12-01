#include "Pawn.hh"

Pawn::Pawn(PieceColor pColor, Coordinate pPosition)
{
  color = pColor;
  position = pPosition;
  switch (color)
  {
  case PieceColor::WHITE:
    character = "♟︎";
    break;
  case PieceColor::BLACK:
    character = "♙";
    break;
  default:
    break;
  }

  switch (color)
  {
  case PieceColor::WHITE:
    literalCharacter = 'P';
    break;
  case PieceColor::BLACK:
    literalCharacter = 'p';
    break;
  default:
    break;
  }
}

std::string Pawn::toString(bool literal) const
{
  if (literal) return std::string(1, literalCharacter);
  return character;
}

std::vector<Coordinate> Pawn::listValidCoordinate() const
{
    return std::vector<Coordinate>();
}