#pragma once

#include "Coordinate.hh"
#include "Piece.hh"

/**
 * The class representing the bishops.
 * It inherits from the `Piece` class.
 */
class Bishop : public Piece
{
public:
  Bishop(PieceColor pColor, Coordinate pPosition);
  ~Bishop() override = default;

  MoveType IsMoveValid(const Coordinate endingPosition) const override;
};
