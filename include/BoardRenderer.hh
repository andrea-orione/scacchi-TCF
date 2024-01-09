#pragma once

#include "Piece.hh"

class BoardRenderer
{
public:
  virtual ~BoardRenderer() = default;

  void PrintBoard(PieceColor playerColor) const;
  virtual void PrintWhiteBoard() const = 0;
  virtual void PrintBlackBoard() const = 0;
};
