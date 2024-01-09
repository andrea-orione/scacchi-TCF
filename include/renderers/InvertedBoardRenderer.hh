#pragma once

#include "BoardRenderer.hh"

class InvertedBoardRenderer : public BoardRenderer
{
public:
  InvertedBoardRenderer() {}
  ~InvertedBoardRenderer() override = default;
  void PrintWhiteBoard() const override;
  void PrintBlackBoard() const override;
};
