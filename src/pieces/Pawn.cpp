#include "Pawn.hh"

Pawn::Pawn(PieceColor pColor): color(pColor)
{
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
  if (literal) return std::to_string(literalCharacter);
  return character;
}

std::vector<Coordinate> Pawn::listValidCoordinate() const
{
    return std::vector<Coordinate>();
}