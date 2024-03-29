#pragma once
 
#include "BoardRenderer.hh"

class NormalBoardRenderer : public BoardRenderer
{
public:
  NormalBoardRenderer();
  ~NormalBoardRenderer() override = default;

private:
  void PrintWhiteBoard() const override;
  void PrintBlackBoard() const override;
};
