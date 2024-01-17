#include "King.hh"

#include "Board.hh"
#include "Coordinate.hh"
#include "Movement.hh"
#include "Piece.hh"
#include "Utils.hh"

#include <stdexcept>

King::King(PieceColor pColor, Coordinate pPosition, bool pHasMoved)
{
  if (pColor == PieceColor::VOID)
    throw std::invalid_argument("King constructor: VOID is invalid Color for a king.");

  color = pColor;
  pieceType = PieceType::KING;
  position = pPosition;
  hasMoved = pHasMoved;
}

MoveType King::IsMoveValid(const Coordinate endingPosition) const
{
  // Too far case
  if (this->position.SquaredDistance(endingPosition) > 4)
    return MoveType::INVALID;

  // Normal move case
  const Board &board = Board::Instance();
  if (this->position.SquaredDistance(endingPosition) < 3)
  {
    return (board.GetPiece(endingPosition)->GetColor() != this->color) ? MoveType::NORMAL : MoveType::INVALID;
  }

  // Castles
  const int xDistance = endingPosition.GetX() - this->position.GetX();
  const int yDistance = endingPosition.GetY() - this->position.GetY();

  if (yDistance != 0 || this->position.GetX() != 5)
    return MoveType::INVALID;

  // Chooses direction
  const Movement direction(utils::sgn(xDistance), 0);
  const int rookXPosition = (direction.GetX() > 0) ? 8 : 1;
  const Coordinate rookPosition(rookXPosition, this->position.GetY());
  // Checks whether there is the rook and if eather one of them has moved
  if (!(board.GetPiece(rookPosition)->CanCastle() && this->CanCastle()))
    return MoveType::INVALID;

  // Checks that all square are void (check condition checked in Board function to avoid recursive calls)
  for (Coordinate newPosition = this->GetPosition() + direction; newPosition != rookPosition; newPosition += direction)
  {
    if (board.GetPiece(newPosition)->GetColor() != PieceColor::VOID)
      return MoveType::INVALID;
  }
  return MoveType::CASTLING;
}

void King::Move(const Coordinate newPosition)
{
  position = newPosition;
  hasMoved = true;
}
