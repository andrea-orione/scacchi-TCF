#pragma once
// ♔ ♕ ♖ ♗ ♘ ♙ ♚ ♛ ♜ ♝ ♞ ♟︎ Unicode characters to use later

#include "Coordinate.hh"
#include <string>
#include <vector>

using std::string;
using std::vector;

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
  PieceColor type;

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
