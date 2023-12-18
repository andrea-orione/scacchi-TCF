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
  character = " ";
  literalCharacter = ' ';
}

std::string VoidPiece::toString(bool literal) const
{
  if (literal)
    return std::string(1, literalCharacter);
  return character;
}

bool VoidPiece::isMoveValid(const Coordinate endingPosition) const
{
  return false;
}
