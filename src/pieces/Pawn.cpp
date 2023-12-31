#include "Pawn.hh"
#include "Movement.hh"
#include "Piece.hh"
#include "Board.hh"
#include "Utils.hh"

Pawn::Pawn(PieceColor pColor, Coordinate pPosition, bool pHasMoved) : hasMoved(pHasMoved), doubleAdvancementMoveNumber(-2)
{
  pieceType = PieceType::PAWN;
  color = pColor;
  position = pPosition;

  switch (color)
  {
  case PieceColor::WHITE:
    character = "♟︎";
    coloredCharacter = "♙";
    literalCharacter = 'P';
    break;
  case PieceColor::BLACK:
    character = "♙";
    coloredCharacter = "♟︎";
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

  // generally non allowed movements (under any circumstances)
  if (abs(xDistance) > 1)
    return false;
  if (yDistance * yDirection > 2 || yDistance * yDirection < 1)
    return false;
  if (this->hasMoved && yDistance * yDirection != 1)
    return false;
  if (yDistance * yDirection == 2 && xDistance != 0)
    return false;

  // board instance
  Board &board = Board::Instance();

  // check if landing square is free and the square in front is free (for double advancement moves alsso)
  std::shared_ptr<Piece> endingPositionPiece = board.GetPiece(endingPosition);

  if (abs(yDistance) == 2)
  {
    const Movement forwardMovement(0, yDirection);
    const Coordinate inFrontPosition = this->GetPosition() + forwardMovement;
    std::shared_ptr<Piece> inFrontPiece = board.GetPiece(inFrontPosition);

    if (inFrontPiece->GetColor() != PieceColor::VOID)
      return false;
  }

  // check en passant
  if (abs(xDistance) == 1 && endingPositionPiece->GetColor() == PieceColor::VOID)
  {

    const Coordinate pawnStartingPosition = this->GetPosition();
    const Movement capturingMovement = (this->GetColor() == PieceColor::WHITE) ? Movement(0, -1) : Movement(0, 1);
    const Coordinate capturedPawnPosition = endingPosition + capturingMovement;

    std::shared_ptr<Piece> capturedPawn = board.GetPiece(capturedPawnPosition);

    if (!capturedPawn->GetDoubleAdvancementMoveNumber())
      return false;

    if (capturedPawn->GetDoubleAdvancementMoveNumber() - board.GetMoveNumber() < 2)
    {
      throw EnPassantSignal();
    }
  }

  return !(abs(xDistance) == 1 && endingPositionPiece->GetColor() != !this->GetColor());
}

std::string Pawn::ToString(bool simplified, bool colored) const
{
  if (simplified)
    return std::string(1, literalCharacter);
  if (colored)
    return coloredCharacter;
  return character;
}

void Pawn::Move(const Coordinate newPosition)
{
  Board &boardInstance = Board::Instance();
  int distanceSquared = this->position.SquaredDistance(newPosition);
  // the distanceSquared == 0 case is used when the FEN position is loaded (for loading the last movement for the en passant)
  if (distanceSquared == 0 || distanceSquared == 4)
    doubleAdvancementMoveNumber = boardInstance.GetMoveNumber();
  position = newPosition;
  hasMoved = true;
}
