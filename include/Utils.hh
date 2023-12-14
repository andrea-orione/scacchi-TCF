#pragma once

#include <exception>

#include "Piece.hh"
namespace utils
{
  int sgn(const int value);
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
  const char *what()
  {
    return "InvalidMoveException: This move is invalid";
  }
};