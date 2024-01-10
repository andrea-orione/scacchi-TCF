#include "King.hh"
#include "Board.hh"
#include "Coordinate.hh"
#include "Movement.hh"
#include "Piece.hh"
#include "Utils.hh"
#include <memory>

King::King(PieceColor pColor, Coordinate pPosition, bool pHasMoved)
{
  pieceType = PieceType::KING;
  color = pColor;
  position = pPosition;
  hasMoved = pHasMoved;
}

bool King::IsMoveValid(const Coordinate endingPosition) const
{
  // Too far case
  if (this->position.SquaredDistance(endingPosition) > 4)
    return false;

  // Normal move case
  Board &boardInstance = Board::Instance();
  if (this->position.SquaredDistance(endingPosition) < 3)
  {
    std::shared_ptr<Piece> newSquarePiece = boardInstance.GetPiece(endingPosition);
    return (newSquarePiece->GetColor() != this->color);
  }

  // Castles
  const int xDistance = endingPosition.GetX() - this->position.GetX();
  const int yDistance = endingPosition.GetY() - this->position.GetY();

  if (yDistance != 0 || this->position.GetX() != 5)
    return false;

  // Chooses direction
  Movement direction(utils::sgn(xDistance), 0);
  int rookXPosition = (direction.GetX() > 0) ? 8 : 1;
  Coordinate rookPosition(rookXPosition, this->position.GetY());
  // Checks whether there is the rook and if eather one of them has moved
  std::shared_ptr<Piece> castlingRook = boardInstance.GetPiece(rookPosition);
  if (!castlingRook->CanCastle() || !this->CanCastle())
    return false;

  // Checks that all square are void (check condition checked in Board function to avoid recursive calls)
  for (Coordinate newPosition = this->GetPosition() + direction; newPosition != rookPosition; newPosition += direction)
  {
    if (boardInstance.GetPiece(newPosition)->GetColor() != PieceColor::VOID)
      return false;
  }
  throw CastlingSignal();
}

void King::Move(const Coordinate newPosition)
{
  position = newPosition;
  hasMoved = true;
}
