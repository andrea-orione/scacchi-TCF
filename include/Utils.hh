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
  std::string what()
  {
    return "The notation used does not correspond to a valid move.";
  }
};