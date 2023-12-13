#include "Rook.hh"
#include "Board.hh"
#include "Coordinate.hh"
#include "Movement.hh"
#include "Piece.hh"
#include "Utils.hh"
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
  const int xDistance = endingPosition.getX() - this->position.getX();
  const int yDistance = endingPosition.getY() - this->position.getY();

  // Check whether the endingPosition in the same line or column
  if (xDistance != 0 && yDistance != 0)
    return false;

  // Choose direction
  Board &board = Board::Instance();
  Movement baseMove(utils::sgn(xDistance), utils::sgn(yDistance));

  // Check whether the endingPosition is a free square or occupied by an opponent's piece.
  std::shared_ptr<Piece> endingPositionPiece = board.getPiece(endingPosition);
  if (endingPositionPiece != nullptr)
    if (endingPositionPiece->getColor() == this->color)
      return false;

  // Check whether there are other pieces in the way.
  for (Coordinate newPosition = this->position + baseMove; newPosition != endingPosition; newPosition += baseMove)
  {
    std::shared_ptr<Piece> newSquarePiece = board.getPiece(newPosition);
    if (newSquarePiece != nullptr)
      return false;
  }
  return true;
}

std::string Rook::toString(bool literal) const
{
  if (literal)
    return std::string(1, literalCharacter);
  return character;
}
