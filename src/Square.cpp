#include "../include/Square.hh"
#include "../include/Piece.hh"
#include <iostream>
#include <string>

Square::Square():
  occupied(false),
  piece(nullptr) {}

Square::Square(Piece *occupyingPiece):
  occupied(true),
  piece(occupyingPiece) {}

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

void Square::printSquareContent(bool simplified) const {
  if (!occupied) std::cout << " ";
  else std::cout << piece->toString(simplified);
}

std::string Square::toString(bool simplified) const {
  if (!occupied) return " ";
  else return piece->toString(simplified);
}
