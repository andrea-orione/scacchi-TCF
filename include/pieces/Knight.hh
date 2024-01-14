#pragma once

#include "Coordinate.hh"
#include "Piece.hh"

/**
 * The class representing the knights.
 * It inherits from the `Piece` class.
 */
class Knight : public Piece
{
public:
  Knight(PieceColor pColor, Coordinate pPosition);
  ~Knight() override = default;

  struct MoveInfo IsMoveValid(const Coordinate endingPosition) const override;
};
