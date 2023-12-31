#pragma once

#include <string>

#include "Coordinate.hh"
#include "Piece.hh"

/**
 * The class representing the kings.
 * It inherits from the `Piece` class.
 */
class King : public Piece
{
public:
  King(PieceColor pColor, Coordinate pPosition, bool pHasMoved = false);
  ~King() override = default;

  std::string ToString(bool simplified = false, bool colored = false) const override;
  bool IsMoveValid(const Coordinate endingPosition) const override;

  bool CanCastle() const override { return !hasMoved; }
  void Move(const Coordinate newPosition) override;

private:
  bool hasMoved;
};
