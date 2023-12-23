#pragma once

#include <string>
#include <vector>

#include "Piece.hh"
#include "Coordinate.hh"

/**
 * The class representing the queens.
 * It inherits from the `Piece` class.
 */
class Queen : public Piece
{
public:
    Queen(PieceColor pColor, Coordinate pPosition);
    ~Queen() override = default;

    std::string ToString(bool simplified = false) const override;

    bool IsMoveValid(const Coordinate endingPosition) const override;
};