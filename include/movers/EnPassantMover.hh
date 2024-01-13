#pragma once

#include "PieceMover.hh"

class EnPassantMover : public PieceMover
{
public:
  EnPassantMover() {}
  ~EnPassantMover() override = default;

  void Move(std::shared_ptr<Piece> &&movingPiece, Coordinate endingPosition) const override;
};
