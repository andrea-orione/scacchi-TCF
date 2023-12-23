#pragma once

#include <string>
#include <vector>

#include "Piece.hh"
#include "Coordinate.hh"

/**
 * The class representing the bishops.
 * It inherits from the `Piece` class.
 */
class Bishop : public Piece
{
public:
    Bishop(PieceColor pColor, Coordinate pPosition);
    ~Bishop() override = default;

    std::string ToString(bool simplified = false) const override;

    bool IsMoveValid(const Coordinate endingPosition) const override;
};