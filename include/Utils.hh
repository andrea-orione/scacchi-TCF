#pragma once

#include <exception>
#include <iostream>

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

  /**
   * Clears the screen.
   *
   * Prints to screen the character <ESC>c (in octal ASCII encoding 033c)
   * that toggles terminal control sequence for resetting the console
   * (valid for most of the terminal emulators).
   */
  inline void clear() { std::cout << "\033c" << std::flush; }
} // namespace utils

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
  const char *what() { return message; }

private:
  const char *message;
};

class CastlingSignal : public std::exception
{
};

class EnPassantSignal : public std::exception
{
};

class GuideSignal : public std::exception
{
};

class SettingsSignal : public std::exception
{
};
