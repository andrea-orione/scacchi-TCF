#pragma once

#include "PieceMover.hh"

class PromotionMover : public PieceMover
{
public:
  PromotionMover(const char promotionPiece): promotionPiece(promotionPiece) {}
  ~PromotionMover() override = default;

  void Move(std::shared_ptr<Piece> &&movingPiece, Coordinate endingPosition) const override;
private:
  char promotionPiece;
};
