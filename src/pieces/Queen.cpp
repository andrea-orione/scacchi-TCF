#include "Queen.hh"

Queen::Queen(PieceColor pColor): color(pColor)
{
  switch (color)
  {
  case PieceColor::WHITE:
    character = "♛";
    break;
  case PieceColor::BLACK:
    character = "♕";
    break;
  default:
    break;
  }

  switch (color)
  {
  case PieceColor::WHITE:
    literalCharacter = 'Q';
    break;
  case PieceColor::BLACK:
    literalCharacter = 'q';
    break;
  default:
    break;
  }
}

std::string Queen::toString(bool literal) const
{
  if (literal) return std::to_string(literalCharacter);
  return character;
}

std::vector<Coordinate> Queen::listValidCoordinate() const
{
    return std::vector<Coordinate>();
}