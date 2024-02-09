#include "CastlingMover.hh"

#include "Board.hh"
#include "BoardFactory.hh"
#include "Utils.hh"

/**
 * Function for checking if a castling move is valid and, in that case, updating the board and the internal position of the piece.
 *
 * The function first checks whether if the king is in check or if he should pass through a check. In this case the move is invalid
 * Otherwise the move is valid, so the internal position of the moving piece is updated, and the rook is also moved.
 *
 * @param[in] king A pointer to the king that should move.
 * @param[in] kingEndingPosition The coordinate of the square that should be reached.
 */
void CastlingMover::Move(std::shared_ptr<Piece> king, Coordinate kingEndingPosition) const
{
  Board &board = Board::Instance();

  // Preliminary control that the king isn't in check
  const Coordinate kingStartingPosition = king->GetPosition();
  if (board.IsKingInCheck(king->GetColor()))
    throw InvalidMoveException("Castling is not allowed. The king is in check.");

  const int rookY = kingStartingPosition.GetY();
  const Coordinate rookStartingPosition = (kingEndingPosition.GetX() == 7) ? Coordinate(8, rookY) : Coordinate(1, rookY);
  const Coordinate rookEndingPosition = (kingEndingPosition.GetX() == 7) ? Coordinate(6, rookY) : Coordinate(4, rookY);
  board.UpdateSquare(kingEndingPosition, board.GetPiece(kingStartingPosition));
  board.UpdateSquare(rookEndingPosition, board.GetPiece(rookStartingPosition));
  board.UpdateSquare(kingStartingPosition, BoardFactory::MakePiece(0, kingStartingPosition));
  board.UpdateSquare(rookStartingPosition, BoardFactory::MakePiece(0, rookStartingPosition));

  if (!(board.IsSquareAttacked(kingEndingPosition, !(king->GetColor())) || board.IsSquareAttacked(rookEndingPosition, !(king->GetColor()))))
  {
    board.GetPiece(kingEndingPosition)->Move(kingEndingPosition);
    board.GetPiece(rookEndingPosition)->Move(rookEndingPosition);
    return;
  }

  board.UpdateSquare(kingStartingPosition, board.GetPiece(kingEndingPosition));
  board.UpdateSquare(rookStartingPosition, board.GetPiece(rookEndingPosition));
  board.UpdateSquare(kingEndingPosition, BoardFactory::MakePiece(0, kingEndingPosition));
  board.UpdateSquare(rookEndingPosition, BoardFactory::MakePiece(0, rookEndingPosition));
  throw InvalidMoveException("Castling is not allowed. The king cannot pass through or end in check.");
}
