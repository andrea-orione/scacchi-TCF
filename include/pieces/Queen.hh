#pragma once

#include "Coordinate.hh"
#include "Piece.hh"

/**
 * The class representing the queens.
 * It inherits from the `Piece` class.
 */
class Queen : public Piece
{
public:
  Queen(PieceColor pColor, Coordinate pPosition);
  ~Queen() override = default;

  bool IsMoveValid(const Coordinate endingPosition) const override;
};
