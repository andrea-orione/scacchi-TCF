#include "King.hh"
#include "Board.hh"
#include "Coordinate.hh"
#include "Movement.hh"
#include "Piece.hh"
#include "Rook.hh"
#include <memory>
#include <stdexcept>

King::King(PieceColor pColor, Coordinate pPosition)
{
  color = pColor;
  position = pPosition;
  switch (color)
  {
  case PieceColor::WHITE:
    character = "♚";
    literalCharacter = 'K';
    break;
  case PieceColor::BLACK:
    character = "♔";
    literalCharacter = 'k';
    break;
  default:
    break;
  }
}

bool King::isMoveValid(const Coordinate &endingPosition) const
{
  // Too far case
  if (this->position.squaredDistance(endingPosition) > 4) return false;

  // Normal move case
  Board &boardInstance = Board::Instance();
  if (this->position.squaredDistance(endingPosition) < 3) {
    std::shared_ptr<Piece> newSquarePiece = boardInstance.getPiece(endingPosition);
    if (newSquarePiece == nullptr) return true;
    return (newSquarePiece->getColor() != color);
  }

  // Castles
  if (this->position.getY() != endingPosition.getY() || this->position.getX() != 5) return false;
  // Chooses direction
  Movement direction(1,0);
  int limit = 3;
  if ((this->position + direction).squaredDistance(endingPosition) > this->position.squaredDistance(endingPosition)) 
  {
    direction.invertDirection();
    limit = 4;
  }
  // Checks that all square are void
  for (int i=1; i<limit; i++) {
    if (boardInstance.getPiece(this->position + (direction * i)) != nullptr) return false;
  }
  // Checks whether there is the rook ind if eathen one of them has moved
  Coordinate rookPosition = this->position + (direction * limit);
  std::shared_ptr<Rook> castlingRook = std::dynamic_pointer_cast<Rook>(boardInstance.getPiece(rookPosition));
  if (castlingRook == nullptr) return false;
  return !(castlingRook->getHasMoved() || hasMoved); 
}

std::string King::toString(bool literal) const
{
  if (literal)
    return std::string(1, literalCharacter);
  return character;
}
