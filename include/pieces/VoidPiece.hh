#pragma once

#include <string>

#include "Coordinate.hh"
#include "Piece.hh"

/**
 * The class representing empty squares.
 * It inherits from the `Piece` class.
 */
class VoidPiece : public Piece
{
public:
  VoidPiece(Coordinate pPosition);
  ~VoidPiece() override = default;

  std::string ToString(bool simplified = true) const override;
  bool IsMoveValid(const Coordinate endingPosition) const override;
};
