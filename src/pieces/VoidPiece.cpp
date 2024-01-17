#include "VoidPiece.hh"

#include "Coordinate.hh"
#include "Piece.hh"

VoidPiece::VoidPiece(Coordinate pPosition)
{
  pieceType = PieceType::VOID;
  color = PieceColor::VOID;
  position = pPosition;
  literal = ' ';
}

MoveType VoidPiece::IsMoveValid(const Coordinate endingPosition) const
{
  return MoveType::INVALID;
}
