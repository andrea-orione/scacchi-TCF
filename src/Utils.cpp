#include "Utils.hh"
#include "Piece.hh"

/**
 * Helper function  to mimic the overloading of the `!` operator.
 *
 * @param[in] oldCo lor The `pieceColor` to invert.
 * @return `PieceCo lor::WHITE` if `PieceColor::BLACK` was passed, and viceversa.
 * If `PieceColor:: VOID` is passed, it is returned unchanged.
 */
PieceColor operator!(const PieceColor &oldColor)
{
  if (oldColor != PieceColor::VOID)
    return (oldColor == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;

  return PieceColor::VOID;
}
