#pragma once

#include <memory>

#include "Coordinate.hh"
#include "Piece.hh"

class PieceMover
{
public:
  virtual ~PieceMover() = default;

  /**
   * Function for checking if a move is valid and, in that case, updating the board and the internal position of the piece.
   *
   * The function first checks whether the piece can reach the endingPosition.
   * Then updates temporarily the board storing the eventual captured piece in a temporary variable.
   * It checks if in the new position the king of the movingColor is under check.
   * In that case the move is invalid, so the previous position is restored and an error is thrown.
   * Otherwise the move is valid, so the internal position of the moving piece is updated,
   * and the eventual captured piece is stored into the capturedPieces vector of the opposing team.
   * If the move is a castle or en-passant, an exception is thrown by the `IsMoveValid` method of the moving piece.
   * In that case the exception is caught and the validity check is delegated to the proper methods.
   *
   * @param[in] movingPiece A pointer to the piece that should move.
   * @param[in] endingPosition The coordinate of the square that should be reached.
   */
  virtual void Move(std::shared_ptr<Piece> movingPiece, const Coordinate endingPosition) const = 0;
};
