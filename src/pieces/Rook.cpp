#include "Rook.hh"

#include "Board.hh"
#include "Coordinate.hh"
#include "Movement.hh"
#include "Piece.hh"
#include "PieceMover.hh"
#include "Utils.hh"

#include <memory>
#include <stdexcept>

Rook::Rook(PieceColor pColor, Coordinate pPosition, bool pHasMoved)
{
  if (pColor == PieceColor::VOID)
    throw std::invalid_argument("Rook constructor: VOID is invalid Color for a rook.");

  color = pColor;
  pieceType = PieceType::ROOK;
  position = pPosition;
  hasMoved = pHasMoved;
  literal = (color == PieceColor::WHITE) ? 'R' : 'r';
}

bool Rook::IsMoveValid(const Coordinate endingPosition, std::unique_ptr<PieceMover> &moveHandler) const
{
  const int xDistance = endingPosition.GetX() - this->position.GetX();
  const int yDistance = endingPosition.GetY() - this->position.GetY();

  // Check whether the endingPosition in the same line or column
  if (xDistance != 0 && yDistance != 0)
    return false;

  // Choose direction
  const Board &board = Board::Instance();
  const Movement baseMove(utils::sgn(xDistance), utils::sgn(yDistance));

  // Check whether the endingPosition is a free square or occupied by an opponent's piece.
  if (board.GetPiece(endingPosition)->GetColor() == this->color)
    return false;

  // Check whether there are other pieces in the way.
  for (Coordinate newPosition = this->GetPosition() + baseMove; newPosition != endingPosition; newPosition += baseMove)
  {
    if (board.GetPiece(newPosition)->GetColor() != PieceColor::VOID)
      return false;
  }
  return true;
}

void Rook::Move(const Coordinate newPosition)
{
  position = newPosition;
  // the distanceSquared == 0 case is used when the FEN position is loaded (for loading the last movement for the en passant)
  hasMoved = !(this->GetPosition().SquaredDistance(newPosition) == 0);
}
