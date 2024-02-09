#pragma once

#include "PieceMover.hh"

class NormalMover : public PieceMover
{
public:
  void Move(std::shared_ptr<Piece> movingPiece, Coordinate endingPosition) const override;
};
