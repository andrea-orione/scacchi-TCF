#pragma once

#include <exception>

#include "Piece.hh"

namespace utils
{
  /**
   * The sgn(x) function.
   *
   * @param[in] value The `int` of which to calculate the sgn().
   * @return See sgn(x) definition.
   */
  inline int sgn(const int value) { return (0 < value) - (value < 0); }
}

PieceColor operator!(const PieceColor &oldColor);

/**
 * Class for exceptions due to wrong
 * syntax of the moves to perform.
 */
class InvalidNotationException : public std::exception
{
public:
  const char *what()
  {
    return "InvalidNotationException: The notation used does not correspond to a valid move.";
  }
};

/**
 * Class for exceptions due to moves
 * impossible to perform.
 */
class InvalidMoveException : public std::exception
{
public:
  InvalidMoveException(const char *msg) : message(msg){};
  const char *what()
  {
    return message;
  }

private:
  const char *message;
};

class CastlingSignal : public std::exception
{
};
