#include "VoidPiece.hh"

#include "Piece.hh"

VoidPiece::VoidPiece(Coordinate pPosition)
{
  pieceType = PieceType::VOID;
  color = PieceColor::VOID;
  position = pPosition;
  literalCharacter = ' ';
}

std::string VoidPiece::ToString(bool simplified, bool colored) const
{
  return std::string(1, literalCharacter);
}

bool VoidPiece::IsMoveValid(const Coordinate endingPosition) const
{
  return false;
}
