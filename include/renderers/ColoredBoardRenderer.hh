#pragma once

#include "BoardRenderer.hh"

class ColoredBoardRenderer : public BoardRenderer
{
public:
  ColoredBoardRenderer();
  ~ColoredBoardRenderer() override = default;

private:
  void PrintWhiteBoard() const override;
  void PrintBlackBoard() const override;
};
