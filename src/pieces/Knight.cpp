#include "Knight.hh"

#include "Board.hh"
#include "Piece.hh"

Knight::Knight(PieceColor pColor, Coordinate pPosition)
{
  pieceType = PieceType::KNIGHT;
  color = pColor;
  position = pPosition;
}

bool Knight::IsMoveValid(const Coordinate endingPosition) const
{
  // geometric check
  if (this->position.SquaredDistance(endingPosition) != 5)
    return false;

  // determine if the move is valid
  Board &board = Board::Instance();

  return !(board.GetPiece(endingPosition)->GetColor() == this->color);
}
