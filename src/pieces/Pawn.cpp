#include "Pawn.hh"

#include "EnPassantMover.hh"
#include "Movement.hh"
#include "NormalMover.hh"
#include "Piece.hh"
#include "Board.hh"
#include "Utils.hh"
#include <memory>

Pawn::Pawn(PieceColor pColor, Coordinate pPosition, bool pHasMoved) :
  hasMoved(pHasMoved),
  doubleAdvancementMoveNumber(-1)
{
  if (pColor == PieceColor::VOID)
    throw std::invalid_argument("Pawn constructor: VOID is invalid Color for a pawn.");

  pieceType = PieceType::PAWN;
  color = pColor;
  position = pPosition;
}

MoveInfo Pawn::IsMoveValid(const Coordinate endingPosition) const
{
  const Coordinate pawnStartingPosition = this->GetPosition();
  // geometric check
  const int absXDistance = abs(endingPosition.GetX() - pawnStartingPosition.GetX());
  const int yDistance = endingPosition.GetY() - pawnStartingPosition.GetY();

  const int yDirection = (this->GetColor() == PieceColor::WHITE) ? 1 : -1;

  // generally non allowed movements (under any circumstances)
  const bool generalMoveInvalid = absXDistance > 1 || yDistance * yDirection > 2 || yDistance * yDirection < 1;
  const bool doubleMoveInvalid = (this->hasMoved && yDistance * yDirection != 1) || (yDistance * yDirection == 2 && absXDistance != 0);
  if (generalMoveInvalid || doubleMoveInvalid)
    return {false, std::make_unique<NormalMover>()};

  // board instance
  const Board &board = Board::Instance();

  // check if landing square is free and the square in front is free (for double advancement moves also)
  if (abs(yDistance) == 2)
  {
    const Movement forwardMovement(0, yDirection);
    const Coordinate inFrontPosition = this->GetPosition() + forwardMovement; 

    return {(board.GetPiece(inFrontPosition)->GetColor() == PieceColor::VOID && board.GetPiece(endingPosition)->GetColor() == PieceColor::VOID), std::make_unique<NormalMover>()};
  }

  // check en passant
  if (absXDistance == 1 && board.GetPiece(endingPosition)->GetColor() == PieceColor::VOID)
  {
    const Movement capturingMovement = (this->GetColor() == PieceColor::WHITE) ? Movement(0, -1) : Movement(0, 1);
    const Coordinate capturedPawnPosition = endingPosition + capturingMovement;

    const int doubleAdvNum = board.GetPiece(capturedPawnPosition)->GetDoubleAdvancementMoveNumber();
    if (doubleAdvNum==-1 || abs(doubleAdvNum - board.GetMoveNumber()) > 1)
      return {false, std::make_unique<EnPassantMover>()};

    return {true, std::make_unique<EnPassantMover>()};
  }

  return {!(absXDistance == 1 && board.GetPiece(endingPosition)->GetColor() != !this->GetColor()), std::make_unique<NormalMover>()};
}

void Pawn::Move(const Coordinate newPosition)
{
  const Board &board = Board::Instance();
  const int distanceSquared = this->position.SquaredDistance(newPosition);
  // the distanceSquared == 0 case is used when the FEN position is loaded (for loading the last movement for the en passant)
  if (distanceSquared == 0 || distanceSquared == 4)
    doubleAdvancementMoveNumber = board.GetMoveNumber();
  position = newPosition;
  hasMoved = true;
}
