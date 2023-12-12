#include "Rook.hh"
#include "Board.hh"
#include "Coordinate.hh"
#include "Movement.hh"
#include "Piece.hh"
#include <memory>
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

bool Rook::isMoveValid(const Coordinate &endingPosition) const
{
  // Check whether the endingPosition in the same line or column
  if ((this->position.getX() != endingPosition.getX()) && (this->position.getY() != endingPosition.getY())) return false;

  // Choose direction
  Board &boardInstance = Board::Instance();
  Movement direction(0,0);
  (this->position.getX() == endingPosition.getX()) ? direction.setY(1) : direction.setX(1);
  if ((this->position+direction).squaredDistance(endingPosition) > this->position.squaredDistance(endingPosition))
    direction.invertDirection();

  // Check whether the endingPosition is a free square or occupied by an opponent's piece.
  std::shared_ptr<Piece> endingPositionPiece = boardInstance.getPiece(endingPosition);
  if (endingPositionPiece != nullptr)
    if (endingPositionPiece->getColor() == color)
      return false;

  // Check whether there are other pieces in the way.
  for (Coordinate newPosition = this->position+direction; newPosition != endingPosition; newPosition += direction) {
    std::shared_ptr<Piece> newSquarePiece = boardInstance.getPiece(newPosition);
    if (newSquarePiece != nullptr) return false;
  }
  return true;
}

std::string Rook::toString(bool literal) const
{
  if (literal)
    return std::string(1, literalCharacter);
  return character;
}
