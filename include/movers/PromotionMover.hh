#pragma once

#include "PieceMover.hh"

class PromotionMover : public PieceMover
{
public:
  PromotionMover(char promotionPiece): promotionPiece(promotionPiece) {}

  void Move(Piece* movingPiece, const Coordinate endingPosition) const override;
private:
  char promotionPiece;
};
