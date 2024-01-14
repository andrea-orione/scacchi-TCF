#pragma once

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

  char GetChar() const override { char literal = ' '; return literal; }

  struct MoveInfo IsMoveValid(const Coordinate endingPosition) const override;
};
