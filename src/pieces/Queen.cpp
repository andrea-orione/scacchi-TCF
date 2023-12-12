#include "Queen.hh"

#include <memory>

#include "Board.hh"

Queen::Queen(PieceColor pColor, Coordinate pPosition)
{
  color = pColor;
  position = pPosition;
  switch (color)
  {
  case PieceColor::WHITE:
    character = "♛";
    literalCharacter = 'Q';
    break;
  case PieceColor::BLACK:
    character = "♕";
    literalCharacter = 'q';
    break;
  default:
    break;
  }
}

std::string Queen::toString(bool literal) const
{
  if (literal)
    return std::string(1, literalCharacter);
  return character;
}

bool Queen::isMoveValid(const Coordinate &endingPosition) const
{
  const int xDistance = endingPosition.getX() - this->position.getX();
  const int yDistance = endingPosition.getY() - this->position.getY();

  // geometric check
  if (abs(xDistance) != abs(yDistance) || (xDistance != 0 && yDistance != 0))
    return false;

  // determine direction
  Movement baseMove(sgn(xDistance), sgn(yDistance));

  // determine if the move is valid
  Board &board = Board::Instance();

  // check final square
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