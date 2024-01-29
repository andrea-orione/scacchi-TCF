#pragma once

#include "PieceMover.hh"

class CastlingMover : public PieceMover
{
public:
  CastlingMover() {}
  ~CastlingMover() override = default;

  void Move(std::shared_ptr<Piece> movingPiece, const Coordinate endingPosition) const override;
};
