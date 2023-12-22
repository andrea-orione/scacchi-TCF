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

    std::string toString(bool simplified = false) const override;

    bool isMoveValid(const Coordinate endingPosition) const override;
};