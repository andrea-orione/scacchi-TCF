#pragma once
//♔ ♕ ♖ ♗ ♘ ♙ ♚ ♛ ♜ ♝ ♞ ♟︎ Unicode characters to use later

#include <string>

//TODO Try implementing void Piece representing an empty square, to replace the Square class (should be useless)
/**
 * The abstract class for the chess Piece.
 */
class Piece
{
public:
  /**
   * Return the string representing the Piece.
   *
   * @return the above described string.
   */
  virtual std::string toString(bool literal=false) = 0;
};
