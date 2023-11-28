#pragma once
// ♔ ♕ ♖ ♗ ♘ ♙ ♚ ♛ ♜ ♝ ♞ ♟︎ Unicode characters to use later

#include "Coordinate.hh"
#include <string>
#include <vector>

using std::string;
using std::vector;

// TODO Try implementing void Piece representing an empty square, to replace the Square class (should be useless)
enum class PieceType
{
  WHITE,
  BLACK,
  EMPTY
};

/**
 * The abstract class for the chess Piece.
 */
class Piece
{
protected:
  PieceType type;

public:
  virtual ~Piece() {}

  /**
   * Return the string representing the Piece.
   *
   * @return The aforementioned string.
   */
  virtual string toString(bool literal = false) const = 0;

  /**
   *
   */
  virtual vector<Coordinate> listValidCoordinate() const = 0;
};
