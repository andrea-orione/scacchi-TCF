#pragma once

#include <map>
#include <memory>
#include <string_view>
#include <vector>

#include "Piece.hh"

class BoardRenderer
{
public:
  virtual ~BoardRenderer() = default;

  void PrintBoard(PieceColor playerColor) const;
  virtual void PrintWhiteBoard() const = 0;
  virtual void PrintBlackBoard() const = 0;
  virtual std::string_view PieceToString(const std::shared_ptr<Piece> piece) const;
  virtual std::string PieceVectorToString(const std::vector<std::shared_ptr<Piece>> pieceVector) const;
protected:
  static const std::map<PieceType, std::string_view> whitePiecesChars;
  static const std::map<PieceType, std::string_view> blackPiecesChars;
};
