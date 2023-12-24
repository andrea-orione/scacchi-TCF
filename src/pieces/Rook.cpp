#include "Rook.hh"
#include "Board.hh"
#include "Coordinate.hh"
#include "Movement.hh"
#include "Piece.hh"
#include "Utils.hh"
#include <memory>
#include <stdexcept>

Rook::Rook(PieceColor pColor, Coordinate pPosition, bool pHasMoved)
{
  if (pColor == PieceColor::VOID)
    throw std::invalid_argument("Rook constructor: VOID is invalid Color for a rook.");
  pieceType = PieceType::ROOK;
  color = pColor;
  position = pPosition;
  hasMoved = pHasMoved;
  switch (color)
  {
  case PieceColor::WHITE:
    character = "♜";
    literalCharacter = 'R';
    break;
  case PieceColor::BLACK:
    character = "♖";
    literalCharacter = 'r';
    break;
  default:
    break;
  }
}

bool Rook::IsMoveValid(const Coordinate endingPosition) const
{
  const int xDistance = endingPosition.GetX() - this->position.GetX();
  const int yDistance = endingPosition.GetY() - this->position.GetY();

  // Check whether the endingPosition in the same line or column
  if (xDistance != 0 && yDistance != 0)
    return false;

  // Choose direction
  Board &board = Board::Instance();
  Movement baseMove(utils::sgn(xDistance), utils::sgn(yDistance));

  // Check whether the endingPosition is a free square or occupied by an opponent's piece.
  std::shared_ptr<Piece> endingPositionPiece = board.GetPiece(endingPosition);
  if (endingPositionPiece->GetColor() == this->color)
    return false;

  // Check whether there are other pieces in the way.
  for (Coordinate newPosition = this->GetPosition() + baseMove; newPosition != endingPosition; newPosition += baseMove)
  {
    std::shared_ptr<Piece> newSquarePiece = board.GetPiece(newPosition);
    if (newSquarePiece->GetColor() != PieceColor::VOID)
      return false;
  }
  return true;
}

std::string Rook::ToString(bool simplified) const
{
  if (simplified)
    return std::string(1, literalCharacter);
  return character;
}

void Rook::Move(const Coordinate newPosition)
{
  position = newPosition;
  hasMoved = true;
}
