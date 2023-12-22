#pragma once

#include <string>
#include <vector>

#include "Piece.hh"
#include "Coordinate.hh"

/**
 * The class representing empty squares.
 * It inherits from the `Piece` class.
 */
class VoidPiece : public Piece
{
public:
  VoidPiece(Coordinate pPosition);
  ~VoidPiece() override = default;

  std::string toString(bool simplified = true) const override;
  bool isMoveValid(const Coordinate endingPosition) const override;
};
