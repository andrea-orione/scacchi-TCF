#pragma once

#include "Coordinate.hh"
#include "Piece.hh"

/**
 * The class representing the rooks.
 * It inherits from the `Piece` class.
 */
class Rook : public Piece
{
public:
  Rook(PieceColor pColor, Coordinate pPosition, bool pHasMoved = false);
  ~Rook() override = default;

  bool IsMoveValid(const Coordinate endingPosition) const override;

  bool CanCastle() const override { return !hasMoved; }

  char GetChar() const { char literal = (this->GetColor() == PieceColor::WHITE) ? 'R' : 'r'; return literal; }
  void Move(const Coordinate newPosition) override;

private:
  bool hasMoved;
};
