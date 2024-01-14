#pragma once

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

  struct MoveInfo IsMoveValid(const Coordinate endingPosition) const override;

  bool CanCastle() const override { return !hasMoved; }
  void Move(const Coordinate newPosition) override;

  char GetChar() const override { char literal = (this->GetColor() == PieceColor::WHITE) ? 'K' : 'k'; return literal; }

private:
  bool hasMoved;
};
