#include "Queen.hh"

#include "Board.hh"
#include "Piece.hh"
#include "Utils.hh"

#include <stdexcept>

Queen::Queen(PieceColor pColor, Coordinate pPosition)
{
  if (pColor == PieceColor::VOID)
    throw std::invalid_argument("Queen constructor: VOID is invalid Color for a queen.");
  
  color = pColor;
  pieceType = PieceType::QUEEN;
  position = pPosition;
  literal = (color == PieceColor::WHITE) ? 'Q' : 'q';
}

MoveType Queen::IsMoveValid(const Coordinate endingPosition) const
{
  const int xDistance = endingPosition.GetX() - this->position.GetX();
  const int yDistance = endingPosition.GetY() - this->position.GetY();

  // geometric check
  if (abs(xDistance) != abs(yDistance) && (xDistance != 0 && yDistance != 0))
    return MoveType::INVALID;

  // determine direction
  const Movement baseMove(utils::sgn(xDistance), utils::sgn(yDistance));

  // determine if the move is valid
  const Board &board = Board::Instance();

  // check final square
  if (board.GetPiece(endingPosition)->GetColor() == this->color)
    return MoveType::INVALID;

  // Check whether there are other pieces in the way.
  for (Coordinate newPosition = this->GetPosition() + baseMove; newPosition != endingPosition; newPosition += baseMove)
  {
    if (board.GetPiece(newPosition)->GetColor() != PieceColor::VOID)
      return MoveType::INVALID;
  }
  return MoveType::NORMAL;
}
