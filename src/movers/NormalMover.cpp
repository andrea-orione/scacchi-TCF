#include "NormalMover.hh"

#include <memory>

#include "Board.hh"
#include "BoardFactory.hh"
#include "Coordinate.hh"
#include "Piece.hh"
#include "Utils.hh"

void NormalMover::Move(std::shared_ptr<Piece> &&movingPiece, const Coordinate endingPosition) const
{
  Board &board = Board::Instance();
  const Coordinate startingPosition = movingPiece->GetPosition();
  std::shared_ptr<Piece> temporaryStorageCapturedPiece = board.GetPiece(endingPosition);
  board.UpdateSquare(endingPosition, movingPiece);
  board.UpdateSquare(startingPosition, BoardFactory::MakePiece(0, startingPosition));

  const bool kingInCheck = (movingPiece->GetType() == PieceType::KING) ?
    board.IsSquareAttacked(endingPosition, !movingPiece->GetColor()) :
    board.IsKingInCheck(movingPiece->GetColor());

  // Valid move case
  if (!kingInCheck)
  {
    movingPiece->Move(endingPosition);
    board.AddCapturedPiece(temporaryStorageCapturedPiece);
    return;
  }

  // Invalid move case. Resetting the board.
  board.UpdateSquare(startingPosition, movingPiece);
  board.UpdateSquare(endingPosition, temporaryStorageCapturedPiece);
  throw InvalidMoveException("This move is not allowed. The king would be in check.");
}
