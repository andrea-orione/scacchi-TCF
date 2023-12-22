#include "Pawn.hh"
#include "Piece.hh"
#include "Board.hh"
#include "Utils.hh"

Pawn::Pawn(PieceColor pColor, Coordinate pPosition, bool pHasMoved)
{
  pieceType = PieceType::PAWN;
  color = pColor;
  position = pPosition;
  hasMoved = pHasMoved;
  doubleAdvancementMoveNumber = -2;
  switch (color)
  {
  case PieceColor::WHITE:
    character = "♟︎";
    literalCharacter = 'P';
    break;
  case PieceColor::BLACK:
    character = "♙";
    literalCharacter = 'p';
    break;
  default:
    break;
  }
}

bool Pawn::isMoveValid(const Coordinate endingPosition) const
{
  const int xDistance = endingPosition.getX() - this->position.getX();
  const int yDistance = endingPosition.getY() - this->position.getY();

  const int yDirection = (this->getColor() == PieceColor::WHITE) ? 1 : -1;

  if (abs(xDistance) > 1)
    return false;
  if (yDistance * yDirection > 2 || yDistance * yDirection < 1)
    return false;
  if (this->hasMoved && yDistance * yDirection != 1)
    return false;
  if (yDistance * yDirection == 2 && xDistance != 0)
    return false;

  // mossa

  Board &board = Board::Instance();

  // Check if landing square is free

  std::shared_ptr<Piece> endingPositionPiece = board.getPiece(endingPosition);
  if (xDistance == 0 && endingPositionPiece->getColor() != PieceColor::VOID)
    return false;
  return !(abs(xDistance) == 1 && endingPositionPiece->getColor() != !this->getColor());
}

std::string Pawn::toString(bool simplified) const
{
  if (simplified)
    return std::string(1, literalCharacter);
  return character;
}

void Pawn::move(const Coordinate newPosition)
{
  Board &boardInstance = Board::Instance();
  doubleAdvancementMoveNumber = boardInstance.getMoveNumber();
  position = newPosition;
  hasMoved = true;
}
