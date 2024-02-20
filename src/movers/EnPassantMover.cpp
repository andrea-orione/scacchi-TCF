#include "EnPassantMover.hh"

#include "Board.hh"
#include "Utils.hh"

/**
 * Function for checking if an en-passant move is valid and, in that case, updating the board and the internal position of the piece.
 *
 * The function updates temporarily the board storing the captured piece in a temporary variable.
 * It checks if in the new position the king of the movingColor is under check.
 * In that case the move is invalid, so the previous position is restored and an error is thrown.
 * Otherwise the move is valid, so the internal position of the moving piece is updated,
 * and the eventual captured piece is stored into the capturedPieces vector of the opposing team.
 * If the move is a castle or en-passant, an exception is thrown by the `IsMoveValid` method of the moving piece.
 * In that case the exception is caught and the validity check is delegated to the proper methods.
 *
 * @param[in] pawn A pointer to the pawn that should move.
 * @param[in] pawnEndingPosition The coordinate to the square that should be reached.
 */
void EnPassantMover::Move(Piece* pawn, const Coordinate pawnEndingPosition) const
{
  const Coordinate pawnStartingPosition = pawn->GetPosition();
  const Movement capturingMovement = (pawn->GetColor() == PieceColor::WHITE) ? Movement(0, -1) : Movement(0, 1);
  const Coordinate capturedPawnPosition = pawnEndingPosition + capturingMovement;

  Board &board = Board::Instance();

  std::unique_ptr<Piece> capturedPawn = board.RemovePiece(capturedPawnPosition);
  board.InsertPiece(pawnEndingPosition, board.RemovePiece(pawnStartingPosition));

  // Valid move case
  if (!board.IsKingInCheck(pawn->GetColor()))
  {
    pawn->Move(pawnEndingPosition);
    board.AddCapturedPiece(std::move(capturedPawn));
    return;
  }

  // Invalid move case. Resetting the board.
  board.InsertPiece(pawnStartingPosition, board.RemovePiece(pawnEndingPosition));
  board.InsertPiece(capturedPawnPosition, std::move(capturedPawn));
  throw InvalidMoveException("This move is not allowed. The king would be in check.");
}
