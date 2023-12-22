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

    std::string toString(bool simplified = false) const override;

    bool isMoveValid(const Coordinate endingPosition) const override;
};