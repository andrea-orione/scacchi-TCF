#pragma once

#include <string>
#include <vector>

#include "Piece.hh"
#include "Coordinate.hh"

/**
 * The class representing the rooks.
 * It inherits from the `Piece` class.
 */
class Rook : public Piece
{
public:
  Rook(PieceColor pColor, Coordinate pPosition, bool pHasMoved = false);
  ~Rook() override = default;

  std::string ToString(bool simplified = false) const override;
  bool IsMoveValid(const Coordinate endingPosition) const override;

  bool CanCastle() const override { return !hasMoved; }
  void Move(const Coordinate newPosition) override;

private:
  bool hasMoved;
};
