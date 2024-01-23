#include "Utils.hh"
#include "Piece.hh"

/**
 * Helper function  to mimic the overloading of the `!` operator.
 *
 * @param[in] oldColor The `pieceColor` to invert.
 * @return `PieceColor::WHITE` if `PieceColor::BLACK` was passed, and viceversa.
 * If `PieceColor:: VOID` is passed, it is returned unchanged.
 */
PieceColor operator!(const PieceColor &oldColor)
{
  if (oldColor != PieceColor::VOID)
    return (oldColor == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;

  return PieceColor::VOID;
}

/**
 * Utility to find if there are three equal strings in a sorted vector
 *
 * @param[in] vec The sorted vector of strings.
 * @return true if there are three adjacent items that are the same.
 */
bool utils::adjacent_find(std::vector<std::string> vec)
{
  if (vec.size() < 7)
    return false;
  for (auto i = vec.begin(); i != vec.end() - 2; i++)
  {
    if (*i == *(i + 1) && *i == *(i + 2))
      return true;
  }
  return false;
}
