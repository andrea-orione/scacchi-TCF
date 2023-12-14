#pragma once

#include <string>
#include <vector>

#include "Piece.hh"
#include "Coordinate.hh"

class King : public Piece
{
public:
  King(PieceColor pColor, Coordinate pPosition, bool pHasMoved=false);
  ~King() override = default;

  std::string toString(bool literal = false) const override;
  bool isMoveValid(const Coordinate &endingPosition) const override;

  bool canCastle() const override { return !hasMoved; }
  void move(const Coordinate &newPosition) override; 
private:
  bool hasMoved;
};
