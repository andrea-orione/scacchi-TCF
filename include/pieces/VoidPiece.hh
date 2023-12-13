#pragma once

#include <string>
#include <vector>

#include "Piece.hh"
#include "Coordinate.hh"

class VoidPiece : public Piece
{
public:
  VoidPiece(Coordinate pPosition);
  ~VoidPiece() override = default;

  std::string toString(bool literal = false) const override;
  bool isMoveValid(const Coordinate &endingPosition) const override;
};
