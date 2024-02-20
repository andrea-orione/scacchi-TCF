#include "PromotionMover.hh"

#include "Board.hh"
#include "BoardFactory.hh"
#include "Coordinate.hh"
#include "Piece.hh"
#include "Utils.hh"

#include <memory>

/**
 * Function for promoting a pawn.
 */
void PromotionMover::Move(Piece* pawn, const Coordinate endingPosition) const
{
  Board &board = Board::Instance();

  // promote to the right color
  const char newPieceChar = (pawn->GetColor() == PieceColor::WHITE) ?
    std::toupper(this->promotionPiece) :
    std::tolower(this->promotionPiece);

  const Coordinate startingPosition = pawn->GetPosition();
  std::unique_ptr<Piece> capturedPiece = board.ReplacePiece(endingPosition, BoardFactory::MakePiece(newPieceChar, endingPosition));
  std::unique_ptr<Piece> oldPawn = board.RemovePiece(startingPosition);

  // Valid move case
  if (board.IsKingInCheck(pawn->GetColor()))
  {
    pawn->Move(endingPosition);
    board.AddCapturedPiece(std::move(capturedPiece));
    return;
  }

  // Invalid move case. Resetting the board.
  board.InsertPiece(startingPosition, std::move(oldPawn));
  board.InsertPiece(endingPosition, std::move(capturedPiece));
  throw InvalidMoveException("This move is not allowed. The king would be in check.");
}
