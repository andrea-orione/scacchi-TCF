#include "Queen.hh"

Queen::Queen(PieceColor pColor, Coordinate pPosition)
{
  color = pColor;
  position = pPosition;
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
  if (literal) return std::string(1, literalCharacter);
  return character;
}

std::vector<Coordinate> Queen::listValidCoordinate() const
{
    return std::vector<Coordinate>();
}