#include "NormalMover.hh"

#include <memory>

#include "Coordinate.hh"
#include "Piece.hh"

void NormalMover::Move(std::shared_ptr<Piece> &&movingPiece, const Coordinate endingPosition) const
{
  const Coordinate startingPosition = movingPiece->GetPosition();
  auto &opponentPieceVector = (movingPiece->GetColor() == PieceColor::WHITE) ? blackPieces : whitePieces;
  auto &opponentCapturedPieceVector = (movingPiece->GetColor() == PieceColor::WHITE) ? blackCapturedPieces : whiteCapturedPieces;
  std::shared_ptr<Piece> temporaryStorageCapturedPiece = squaresMap.at(endingPosition);
  squaresMap.at(endingPosition) = movingPiece;
  squaresMap.at(startingPosition) = BoardFactory::MakePiece(0, startingPosition);
  std::shared_ptr<Piece> &friendKing = (movingPiece->GetColor() == PieceColor::WHITE) ? whiteKing : blackKing;
  const Coordinate &friendKingPosition = (friendKing == movingPiece) ? endingPosition : friendKing->GetPosition();
  if (temporaryStorageCapturedPiece->GetColor() != PieceColor::VOID)
    opponentPieceVector.erase(std::find(opponentPieceVector.begin(), opponentPieceVector.end(), temporaryStorageCapturedPiece));

  // Valid move case
  if (!IsSquareAttacked(friendKingPosition, !(movingPiece->GetColor())))
  {
    movingPiece->Move(endingPosition);
    if (temporaryStorageCapturedPiece->GetType() != PieceType::VOID)
      opponentCapturedPieceVector.push_back(temporaryStorageCapturedPiece);
    return;
  }

  // Invalid move case. Resetting the board.
  if (temporaryStorageCapturedPiece->GetColor() != PieceColor::VOID)
    opponentPieceVector.push_back(temporaryStorageCapturedPiece);
  squaresMap.at(startingPosition) = movingPiece;
  squaresMap.at(endingPosition) = temporaryStorageCapturedPiece;
  throw InvalidMoveException("This move is not allowed. The king would be in check.");
}
