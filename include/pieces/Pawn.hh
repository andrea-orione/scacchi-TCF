#pragma once

#include <string>
#include <vector>

#include "Piece.hh"
#include "Coordinate.hh"

class Pawn : public Piece
{
public:
    Pawn(PieceColor pColor, Coordinate pPosition);
    ~Pawn() override = default;

    std::string toString(bool literal = false) const override;

    bool isMoveValid(const Coordinate &startingPosition, const Coordinate &endingPosition) const override;
};
