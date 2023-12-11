#pragma once

#include <string>
#include <vector>

#include "Piece.hh"
#include "Coordinate.hh"

class Knight : public Piece
{
public:
    Knight(PieceColor pColor, Coordinate pPosition);
    ~Knight() override = default;

    std::string toString(bool literal = false) const override;

    bool isMoveValid(const Coordinate &startingPosition, const Coordinate &endingPosition) const override;
};