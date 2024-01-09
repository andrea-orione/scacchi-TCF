#pragma once

#include "BoardRenderer.hh"

class ColoredBoardRenderer : public BoardRenderer
{
public:
  ColoredBoardRenderer() {}
  ~ColoredBoardRenderer() override = default;
  void PrintWhiteBoard() const override;
  void PrintBlackBoard() const override;
};
