#include "VoidPiece.hh"

#include "Coordinate.hh"
#include "NormalMover.hh"
#include "Piece.hh"
#include <memory>

VoidPiece::VoidPiece(Coordinate pPosition)
{
  pieceType = PieceType::VOID;
  color = PieceColor::VOID;
  position = pPosition;
}

MoveInfo VoidPiece::IsMoveValid(const Coordinate endingPosition) const
{
  return {false, std::make_unique<NormalMover>()};
}
