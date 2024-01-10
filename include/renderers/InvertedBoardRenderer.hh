#pragma once

#include <memory>
#include <string_view>

#include "BoardRenderer.hh"
#include "Piece.hh"

class InvertedBoardRenderer : public BoardRenderer
{
public:
  InvertedBoardRenderer() {}
  ~InvertedBoardRenderer() override = default;

  void PrintWhiteBoard() const override;
  void PrintBlackBoard() const override;
  std::string_view PieceToString(const std::shared_ptr<Piece> piece) const override;
};
