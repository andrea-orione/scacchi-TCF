#include "Pawn.hh"

#include "Piece.hh"
#include "Board.hh"
#include "Utils.hh"

Pawn::Pawn(PieceColor pColor, Coordinate pPosition, bool pHasMoved) : hasMoved(pHasMoved),
                                                                      doubleAdvancementMoveNumber(-2)
{
  pieceType = PieceType::PAWN;
  color = pColor;
  position = pPosition;

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

bool Pawn::IsMoveValid(const Coordinate endingPosition) const
{
  // geometric check
  const int xDistance = endingPosition.GetX() - this->position.GetX();
  const int yDistance = endingPosition.GetY() - this->position.GetY();

  const int yDirection = (this->GetColor() == PieceColor::WHITE) ? 1 : -1;

  if (abs(xDistance) > 1)
    return false;
  if (yDistance * yDirection > 2 || yDistance * yDirection < 1)
    return false;
  if (this->hasMoved && yDistance * yDirection != 1)
    return false;
  if (yDistance * yDirection == 2 && xDistance != 0)
    return false;

  // move
  Board &board = Board::Instance();

  // check if landing square is free
  std::shared_ptr<Piece> endingPositionPiece = board.GetPiece(endingPosition);
  if (xDistance == 0 && endingPositionPiece->GetColor() != PieceColor::VOID)
    return false;

  // check en passant
  // if (doubleAdvancementMoveNumber - board.GetMoveNumber() < 2)
  //   throw EnPassantSignal();

  return !(abs(xDistance) == 1 && endingPositionPiece->GetColor() != !this->GetColor());
}

std::string Pawn::ToString(bool simplified) const
{
  if (simplified)
    return std::string(1, literalCharacter);
  return character;
}

void Pawn::Move(const Coordinate newPosition)
{
  Board &boardInstance = Board::Instance();
  int distanceSquared = this->position.SquaredDistance(newPosition);
  if (distanceSquared == 0 || distanceSquared == 4)
    doubleAdvancementMoveNumber = boardInstance.GetMoveNumber();
  position = newPosition;
  hasMoved = true;
}
