#pragma once

#include <memory>
#include <string_view>

#include "Coordinate.hh"
#include "Piece.hh"

class BoardFactory
{
public:
  BoardFactory() {}
  
  static std::unique_ptr<Piece> MakePiece(char pieceChar, Coordinate pPosition, bool hasRookMoved = true);

  void LoadFenPosition(std::string_view fenString) const;
  void InitializeStartingBoard() const;

private:
  void LoadBoardPosition(std::string_view boardString) const;

};
