#pragma once

#include "PieceMover.hh"

class NormalMover : public PieceMover
{
public:
  NormalMover() {}
  ~NormalMover() override = default;

  void Move(std::shared_ptr<Piece> movingPiece, const Coordinate endingPosition) const override;
};
