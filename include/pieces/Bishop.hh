#pragma once

#include "Coordinate.hh"
#include "Piece.hh"
#include "PieceMover.hh"

#include <memory>

/**
 * The class representing the bishops.
 * It inherits from the `Piece` class.
 */
class Bishop : public Piece
{
public:
  Bishop(PieceColor pColor, Coordinate pPosition);
  ~Bishop() override = default;

  bool IsMoveValid(const Coordinate endingPosition, std::unique_ptr<PieceMover> &moveHandler) const override;
};
