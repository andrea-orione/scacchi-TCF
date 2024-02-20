#include "NormalMover.hh"

#include <memory>

#include "Board.hh"
#include "Coordinate.hh"
#include "Piece.hh"
#include "Utils.hh"

void NormalMover::Move(Piece* movingPiece, Coordinate endingPosition) const
{
  Board &board = Board::Instance();
  const Coordinate startingPosition = movingPiece->GetPosition();
  std::unique_ptr<Piece> capturedPiece = board.ReplacePiece(endingPosition, board.RemovePiece(startingPosition));

  const bool kingInCheck = (movingPiece->GetType() == PieceType::KING) ?
    board.IsSquareAttacked(endingPosition, !movingPiece->GetColor()) :
    board.IsKingInCheck(movingPiece->GetColor());

  // Valid move case
  if (!kingInCheck)
  {
    movingPiece->Move(endingPosition);
    board.AddCapturedPiece(std::move(capturedPiece));
    return;
  }

  // Invalid move case. Resetting the board.
  board.InsertPiece(startingPosition, board.ReplacePiece(endingPosition, std::move(capturedPiece)));
  throw InvalidMoveException("This move is not allowed. The king would be in check.");
}
