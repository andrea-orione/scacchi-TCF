#include "Pawn.hh"

Pawn::Pawn(PieceColor pColor, Coordinate pPosition)
{
  color = pColor;
  position = pPosition;
  switch (color)
  {
  case PieceColor::WHITE:
    character = "♟︎";
    literalCharacter = 'P';
    break;
  case PieceColor::BLACK:
    character = "♙";
    literalCharacter = 'p';
    break;
  default:
    break;
  }
}

bool Pawn::isMoveValid(const Coordinate &startingPosition, const Coordinate &endingPosition) const
{
  return true;
}

std::string Pawn::toString(bool literal) const
{
  if (literal)
    return std::string(1, literalCharacter);
  return character;
}
