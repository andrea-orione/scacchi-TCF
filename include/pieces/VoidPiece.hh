#pragma once

#include "Coordinate.hh"
#include "Piece.hh"
#include "PieceMover.hh"

#include <memory>

/**
 * The class representing empty squares.
 * It inherits from the `Piece` class.
 */
class VoidPiece : public Piece
{
public:
  VoidPiece(Coordinate pPosition);
  ~VoidPiece() override = default;

  char GetChar() const { char literal = ' '; return literal; }

  bool IsMoveValid(const Coordinate endingPosition, std::unique_ptr<PieceMover> &moveHandler) const override { return false; }
};
