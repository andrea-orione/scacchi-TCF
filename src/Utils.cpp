#include "Utils.hh"
#include "Piece.hh"

/**
 * Helper function  to mimic the overloading of the `!` operator.
 *
 * @param[in] oldCo lor The `pieceColor` to invert.
 * @return `PieceCo lor::WHITE` if `PieceColor::BLACK` was passed, and viceversa.
 * If `PieceColor:: VOID` is passed, it is returned unchanged.
 */
PieceColor operator!(const PieceColor &oldColor)
{
  if (oldColor != PieceColor::VOID)
    return (oldColor == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;

  return PieceColor::VOID;
}


bool utils::adjacent_find(const std::vector<std::string> &vec)
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