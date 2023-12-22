#pragma once

#include <string>
#include <vector>

#include "Piece.hh"
#include "Coordinate.hh"

/**
 * The class representing the kings.
 * It inherits from the `Piece` class.
 */
class King : public Piece
{
public:
  King(PieceColor pColor, Coordinate pPosition, bool pHasMoved = false);
  ~King() override = default;

  std::string toString(bool simplified = false) const override;
  bool isMoveValid(const Coordinate endingPosition) const override;

  bool canCastle() const override { return !hasMoved; }
  void move(const Coordinate newPosition) override;

private:
  bool hasMoved;
};
