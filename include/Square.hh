#pragma once

#include "Piece.hh"

class Square
{
private:
  bool occupied;
  Piece *piece;

public:
  Square();
  Square(Square &&) = default;
  Square(const Square &) = default;
  Square &operator=(Square &&) = default;
  Square &operator=(const Square &) = default;
  ~Square() = default;

  bool getOccupied() const;
  void setOccupied(bool &);
  Piece *getPiece() const;
  void setPiece(Piece *&);

  void printSquareContent();


};
