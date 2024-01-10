#include "VoidPiece.hh"

#include "Piece.hh"

VoidPiece::VoidPiece(Coordinate pPosition)
{
  pieceType = PieceType::VOID;
  color = PieceColor::VOID;
  position = pPosition;
}

bool VoidPiece::IsMoveValid(const Coordinate endingPosition) const
{
  return false;
}
