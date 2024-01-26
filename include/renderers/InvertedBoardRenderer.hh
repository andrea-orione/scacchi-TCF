#pragma once

#include "BoardRenderer.hh"

class InvertedBoardRenderer : public BoardRenderer
{
public:
  InvertedBoardRenderer();
  ~InvertedBoardRenderer() override = default;

private:
  void PrintWhiteBoard() const override;
  void PrintBlackBoard() const override;
};
