#pragma once

#include <memory>
#include <string_view>

#include "Piece.hh"

class BoardRenderer
{
public:
  virtual ~BoardRenderer() = default;

  void PrintBoard(PieceColor playerColor) const;
  virtual void PrintWhiteBoard() const = 0;
  virtual void PrintBlackBoard() const = 0;
  virtual std::string_view PieceToString(const std::shared_ptr<Piece> piece) const = 0;
};
