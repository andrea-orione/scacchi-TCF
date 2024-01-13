#pragma once

#include "Coordinate.hh"
#include "Piece.hh"
#include "PieceMover.hh"

#include <memory>

/**
 * The class representing the pawns.
 * It inherits from the `Piece` class.
 */
class Pawn : public Piece
{
public:
  Pawn(PieceColor pColor, Coordinate pPosition, bool pHasMoved = false);
  ~Pawn() override = default;

  bool IsMoveValid(const Coordinate endingPosition, std::unique_ptr<PieceMover> &moveHandler) const override;

  char GetChar() const { char literal = (this->GetColor() == PieceColor::WHITE) ? 'P' : 'p'; return literal; }

  void Move(const Coordinate newPosition) override;
  int GetDoubleAdvancementMoveNumber() const override { return doubleAdvancementMoveNumber; }

private:
  bool hasMoved;
  int doubleAdvancementMoveNumber;
};
