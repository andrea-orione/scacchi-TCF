#pragma once

#include "Coordinate.hh"
#include "Piece.hh"

/**
 * The class representing the pawns.
 * It inherits from the `Piece` class.
 */
class Pawn : public Piece
{
public:
  Pawn(PieceColor pColor, Coordinate pPosition, bool pHasMoved = false);
  ~Pawn() override = default;

  MoveType IsMoveValid(const Coordinate endingPosition) const override;

  void Move(const Coordinate newPosition) override;
  int GetDoubleAdvancementMoveNumber() const override { return doubleAdvancementMoveNumber; }

private:
  bool hasMoved;
  int doubleAdvancementMoveNumber;
};
