#pragma once

#include <string>
#include <vector>

#include "Piece.hh"
#include "Coordinate.hh"

class Queen : public Piece
{
public:
    Queen(PieceColor pColor, Coordinate pPosition);
    ~Queen() override = default;

    std::string toString(bool literal = false) const override;

    bool isMoveValid(const Coordinate &endingPosition) const override;
};