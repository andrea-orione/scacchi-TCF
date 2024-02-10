#pragma once

#include "BoardRenderer.hh"
#include "Piece.hh"
#include <vector>

class InvertedBoardRenderer : public BoardRenderer
{
public:
  void PrintWhiteBoard() const override;
  void PrintBlackBoard() const override;

private:
  std::string PieceVectorToString(const std::vector<Piece*>& pieceVector) const;
};
