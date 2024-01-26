#pragma once

#include "BoardRenderer.hh"

class SimplifiedBoardRenderer : public BoardRenderer
{
public:
  SimplifiedBoardRenderer();
  ~SimplifiedBoardRenderer() override = default;

private:
  void PrintWhiteBoard() const override;
  void PrintBlackBoard() const override;
};
