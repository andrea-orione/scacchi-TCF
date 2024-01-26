#pragma once

#include <map>
#include <memory>
#include <string_view>
#include <vector>

#include "Piece.hh"

class BoardRenderer
{
public:
  BoardRenderer(const std::map<PieceType, std::string_view> whitePiecesChars,
                const std::map<PieceType, std::string_view> blackPiecesChars) : whitePiecesChars(whitePiecesChars),
                                                                                blackPiecesChars(blackPiecesChars) {}
  virtual ~BoardRenderer() = default;

  void PrintBoard(PieceColor playerColor) const;
  virtual void PrintWhiteBoard() const = 0;
  virtual void PrintBlackBoard() const = 0;
  std::string_view PieceToString(const std::shared_ptr<Piece> piece, const bool inverted = false) const;
  std::string PieceVectorToString(const std::vector<std::shared_ptr<Piece>> pieceVector, const bool inverted = false) const;
protected:
  const std::map<PieceType, std::string_view> whitePiecesChars;
  const std::map<PieceType, std::string_view> blackPiecesChars;
};
