#pragma once

#include "Coordinate.hh"
#include <string>
#include <vector>

enum class PieceColor
{
  BLACK,
  WHITE
};

/**
 * The abstract class for the chess Piece.
 */
class Piece
{
protected:
  PieceColor color;
  std::string character;
  char literalCharacter;
  Coordinate position;

public:
  virtual ~Piece() {}

  /**
    * Return the string representing the Piece.
    *
    * @return The aforementioned string.
    */
  virtual std::string toString(bool literal = false) const = 0;

  /**
    * Return the vector with valid coordinates.
    * 
    * It creates a vector containing all the coordinates that are reachable
    * by the piece from the square it's in.
    * It take in consideration the limits of the board and the other pieces.
    * Squares with friend pieces cannot be occupied while squares with opponent's
    * pieces can be occupied (capture) but not passed through.
    * 
    * @return The aforementioned vector.
    */
  virtual std::vector<Coordinate> listValidCoordinate() const = 0;
};
