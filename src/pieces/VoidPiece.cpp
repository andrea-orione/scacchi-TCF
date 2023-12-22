#include "VoidPiece.hh"

#include "Movement.hh"
#include "Board.hh"
#include "Piece.hh"
#include "Utils.hh"

VoidPiece::VoidPiece(Coordinate pPosition)
{
  pieceType = PieceType::VOID;
  color = PieceColor::VOID;
  position = pPosition;
  literalCharacter = ' ';
}

std::string VoidPiece::toString(bool simplified) const
{
  return std::string(1, literalCharacter);
}

bool VoidPiece::isMoveValid(const Coordinate endingPosition) const
{
  return false;
}
