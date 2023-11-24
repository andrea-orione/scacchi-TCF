#include "../include/Square.hh"
#include "../include/Piece.hh"
#include <iostream>

Square::Square():
  occupied(false),
  piece(nullptr) {}

bool Square::getOccupied() const {
  return occupied;
}

void Square::setOccupied(bool &newOccupied) {
  occupied = newOccupied;
}

Piece *Square::getPiece() const {
  return piece;
}

void Square::setPiece(Piece *&newPiece) {
  piece = newPiece;
}

void Square::printSquareContent() {
  if (!occupied) std::cout << " ";
  else piece->printPiece();
}
