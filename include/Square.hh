#pragma once

#include "Piece.hh"

class Square
{
private:
  bool occupied;
  Piece *piece;

public:
  Square();
  Square(Piece *occupyingPiece);

  bool getOccupied() const;
  void setOccupied(bool &);
  Piece *getPiece() const;
  void setPiece(Piece *&);

  void printSquareContent();


};
