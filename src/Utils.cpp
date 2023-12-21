#include "Utils.hh"
#include "Piece.hh"
#include <iostream>

/**
 * Helper function to mimic the overloading of the `!` operator.
 *
 * @param[in] oldColor The `pieceColor` to invert.
 * @return `PieceColor::WHITE` if `PieceColor::BLACK` was passed, and viceversa.
 * If `PieceColor::VOID` is passed, it is returned unchanged.
 */
PieceColor operator!(const PieceColor &oldColor)
{
  if (oldColor != PieceColor::VOID)
    return (oldColor == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;

  return PieceColor::VOID;
}
