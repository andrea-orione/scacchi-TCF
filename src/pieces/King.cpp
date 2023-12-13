#include "King.hh"
#include "Board.hh"
#include "Coordinate.hh"
#include "Movement.hh"
#include "Piece.hh"
#include "Rook.hh"
#include "Utils.hh"
#include <memory>
#include <stdexcept>

King::King(PieceColor pColor, Coordinate pPosition)
{
  pieceType = PieceType::KING;
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
  if (this->position.squaredDistance(endingPosition) > 4)
    return false;

  // Normal move case
  Board &boardInstance = Board::Instance();
  if (this->position.squaredDistance(endingPosition) < 3)
  {
    std::shared_ptr<Piece> newSquarePiece = boardInstance.getPiece(endingPosition);
    return (newSquarePiece->getColor() != this->color);
  }

  // Castles
  const int xDistance = endingPosition.getX() - this->position.getX();
  const int yDistance = endingPosition.getY() - this->position.getY();

  if (yDistance != 0 || this->position.getX() != 5)
    return false;

  // Chooses direction
  Movement direction(utils::sgn(xDistance), 0);
  int limit = (direction.getX() > 0) ? 3 : 4;

  // Checks that all square are void (check condition checked in Board function to avoid recursive calls)
  for (int i = 1; i < limit; i++)
  {
    if (boardInstance.getPiece(this->position + (direction * i)) != nullptr)
      return false;
  }

  // Checks whether there is the rook and if eaten one of them has moved
  Coordinate rookPosition = this->position + (direction * limit);
  Rook *castlingRook = dynamic_cast<Rook *>(boardInstance.getPiece(rookPosition).get());
  if (castlingRook)
    return false;
  return !(castlingRook->getHasMoved() || this->hasMoved);
}

std::string King::toString(bool literal) const
{
  if (literal)
    return std::string(1, literalCharacter);
  return character;
}
