#include "Bishop.hh"

#include <memory>
#include <stdexcept>

#include "Movement.hh"
#include "Board.hh"
#include "Piece.hh"
#include "Utils.hh"

Bishop::Bishop(PieceColor pColor, Coordinate pPosition)
{
  pieceType = PieceType::BISHOP;
  color = pColor;
  position = pPosition;
  switch (color)
  {
  case PieceColor::WHITE:
    character = "♝";
    literalCharacter = 'B';
    break;
  case PieceColor::BLACK:
    character = "♗";
    literalCharacter = 'b';
    break;
  default:
    break;
  }
}

std::string Bishop::toString(bool literal) const
{
  if (literal)
    return std::string(1, literalCharacter);
  return character;
}

bool Bishop::isMoveValid(const Coordinate endingPosition) const
{
  const int xDistance = endingPosition.getX() - this->position.getX();
  const int yDistance = endingPosition.getY() - this->position.getY();

  // geometric check
  if (abs(xDistance) != abs(yDistance))
    return false;

  // determine diagonal
  Movement baseMove(utils::sgn(xDistance), utils::sgn(yDistance));

  // determine if the move is valid
  Board &board = Board::Instance();
  std::shared_ptr<Piece> endingPositionPiece = board.getPiece(endingPosition);
  if (endingPositionPiece->getColor() == this->color)
    return false;

  // Check whether there are other pieces in the way.
  for (Coordinate newPosition = this->getPosition() + baseMove; newPosition != endingPosition; newPosition += baseMove)
  {
    if (board.getPiece(newPosition)->getColor() != PieceColor::VOID)
      return false;
  }
  return true;
}
