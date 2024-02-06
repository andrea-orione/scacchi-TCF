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
void PromotionMover::Move(std::shared_ptr<Piece> pawn, const Coordinate endingPosition) const
{
  Board &board = Board::Instance();

  // promote to the right color
  const char newPieceChar = (pawn->GetColor() == PieceColor::WHITE) ?
    std::toupper(this->promotionPiece) :
    std::tolower(this->promotionPiece);

  const Coordinate startingPosition = pawn->GetPosition();
  const std::shared_ptr<Piece> capturedPiece = board.GetPiece(endingPosition);
  board.UpdateSquare(endingPosition, BoardFactory::MakePiece(newPieceChar, endingPosition));
  board.UpdateSquare(startingPosition, BoardFactory::MakePiece(0, startingPosition));

  // Valid move case
  if (board.IsKingInCheck(pawn->GetColor()))
  {
    pawn->Move(endingPosition);
    board.AddCapturedPiece(capturedPiece);
    return;
  }

  // Invalid move case. Resetting the board.
  board.UpdateSquare(startingPosition, pawn);
  board.UpdateSquare(endingPosition, capturedPiece);
  throw InvalidMoveException("This move is not allowed. The king would be in check.");
}
