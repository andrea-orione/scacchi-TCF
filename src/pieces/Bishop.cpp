#include "Bishop.hh"

#include "Movement.hh"
#include "Board.hh"
#include "Piece.hh"
#include "Utils.hh"

#include <stdexcept>

Bishop::Bishop(PieceColor pColor, Coordinate pPosition)
{
  if (pColor == PieceColor::VOID)
    throw std::invalid_argument("Bishop constructor: VOID is invalid Color for a bishop.");

  color = pColor;
  pieceType = PieceType::BISHOP;
  position = pPosition;
}

MoveType Bishop::IsMoveValid(const Coordinate endingPosition) const
{
  const int xDistance = endingPosition.GetX() - this->position.GetX();
  const int yDistance = endingPosition.GetY() - this->position.GetY();

  // geometric check
  if (abs(xDistance) != abs(yDistance))
    return MoveType::INVALID;

  // determine if the move is valid
  const Board &board = Board::Instance();
  if (board.GetPiece(endingPosition)->GetColor() == this->color)
    return MoveType::INVALID;

  // determine diagonal
  const Movement baseMove(utils::sgn(xDistance), utils::sgn(yDistance));

  // Check whether there are other pieces in the way.
  for (Coordinate newPosition = this->GetPosition() + baseMove; newPosition != endingPosition; newPosition += baseMove)
  {
    if (board.GetPiece(newPosition)->GetColor() != PieceColor::VOID)
      return MoveType::INVALID;
  }
  return MoveType::NORMAL;
}
