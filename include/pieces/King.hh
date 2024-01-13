#pragma once

#include "Coordinate.hh"
#include "Piece.hh"
#include "PieceMover.hh"

#include <memory>

/**
 * The class representing the kings.
 * It inherits from the `Piece` class.
 */
class King : public Piece
{
public:
  King(PieceColor pColor, Coordinate pPosition, bool pHasMoved = false);
  ~King() override = default;

  bool IsMoveValid(const Coordinate endingPosition, std::unique_ptr<PieceMover> &moveHandler) const override;

  bool CanCastle() const override { return !hasMoved; }
  void Move(const Coordinate newPosition) override;

  char GetChar() const { char literal = (this->GetColor() == PieceColor::WHITE) ? 'K' : 'k'; return literal; }

private:
  bool hasMoved;
};
