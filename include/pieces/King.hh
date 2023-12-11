#pragma once

#include <string>
#include <vector>

#include "Piece.hh"
#include "Coordinate.hh"

class King : public Piece
{
public:
  King(PieceColor pColor, Coordinate pPosition);
  ~King() override = default;

  std::string toString(bool literal = false) const override;
  bool isMoveValid(const Coordinate &startingPosition, const Coordinate &endingPosition) const override;

  bool getHasMoved() const;
  void setHasMoved(bool newHasMoved);
private:
  bool hasMoved;
};
