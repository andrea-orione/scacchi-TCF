#pragma once

#include "PieceMover.hh"

class CastlingMover : public PieceMover
{
public:
  void Move(Piece* movingPiece, Coordinate endingPosition) const override;
};
