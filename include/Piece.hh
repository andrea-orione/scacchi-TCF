#pragma once
// ♔ ♕ ♖ ♗ ♘ ♙ ♚ ♛ ♜ ♝ ♞ ♟︎ Unicode characters to use later

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
  PieceColor type;

public:
  virtual ~Piece() {}

  /**
   * Return the string representing the Piece.
   *
   * @return The aforementioned string.
   */
  virtual std::string toString(bool literal = false) const = 0;

  /**
   *
   */
  virtual std::vector<Coordinate> listValidCoordinate() const = 0;
};
