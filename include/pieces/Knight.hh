#pragma once

#include <string>
#include <vector>

#include "Piece.hh"
#include "Coordinate.hh"

/**
 * The class representing the knights.
 * It inherits from the `Piece` class.
 */
class Knight : public Piece
{
public:
    Knight(PieceColor pColor, Coordinate pPosition);
    ~Knight() override = default;

    std::string ToString(bool simplified = false) const override;

    bool IsMoveValid(const Coordinate endingPosition) const override;
};