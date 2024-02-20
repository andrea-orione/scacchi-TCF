#pragma once

#include "PieceMover.hh"

class NormalMover : public PieceMover
{
public:
  void Move(Piece* movingPiece, Coordinate endingPosition) const override;
};
