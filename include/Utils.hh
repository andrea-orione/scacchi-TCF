#pragma once

#include <exception>

#include "Piece.hh"
namespace utils
{
  inline int sgn(const int value) { return (0 < value) - (value < 0); }
}

PieceColor operator!(const PieceColor &oldColor);

class InvalidNotationException : public std::exception
{
public:
  const char *what()
  {
    return "InvalidNotationException: The notation used does not correspond to a valid move.";
  }
};

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
