#include "Rook.hh"
#include "Board.hh"
#include "Coordinate.hh"
#include "Movement.hh"
#include <stdexcept>

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

bool Rook::isMoveValid(const Coordinate &startingPosition, const Coordinate &endingPosition) const
{
  if ((startingPosition.getX() != endingPosition.getX()) && (startingPosition.getY() != endingPosition.getY())) return false;

  Board &boardInstance = Board::Instance();
  Movement direction(0,0);
  if (startingPosition.getX() == endingPosition.getX())
  {
    direction.setY(1);
    if ((startingPosition+direction).squaredDistance(endingPosition) > startingPosition.squaredDistance(endingPosition))
      direction.setY(-1);
  } else if (startingPosition.getY() == endingPosition.getY()) {
    direction.setX(1);
    if ((startingPosition+direction).squaredDistance(endingPosition) > startingPosition.squaredDistance(endingPosition))
      direction.setX(-1);
  }

  for (int i = 1; i < 8; i++) {
    try {
      Coordinate newPosition = startingPosition+direction*i;
      if (boardInstance.[newPosition]
    } catch (std::out_of_range) {
    
    }
  
  }
}

std::string Rook::toString(bool literal) const
{
  if (literal)
    return std::string(1, literalCharacter);
  return character;
}
