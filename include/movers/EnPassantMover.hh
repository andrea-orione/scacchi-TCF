#pragma once

#include "PieceMover.hh"

class EnPassantMover : public PieceMover
{
public:
  void Move(Piece* movingPiece, Coordinate endingPosition) const override;
};
