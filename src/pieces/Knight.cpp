#include "Knight.hh"

#include "Board.hh"
#include "Piece.hh"

#include <stdexcept>

Knight::Knight(PieceColor pColor, Coordinate pPosition)
{
  if (pColor == PieceColor::VOID)
    throw std::invalid_argument("Knight constructor: VOID is invalid Color for a knight.");

  color = pColor;
  pieceType = PieceType::KNIGHT;
  position = pPosition;
}

MoveType Knight::IsMoveValid(const Coordinate endingPosition) const
{
  // geometric check
  if (this->position.SquaredDistance(endingPosition) != 5)
    return MoveType::INVALID;

  // determine if the move is valid
  const Board &board = Board::Instance();

  return (board.GetPiece(endingPosition)->GetColor() != this->color) ? MoveType::NORMAL : MoveType::INVALID;
}
