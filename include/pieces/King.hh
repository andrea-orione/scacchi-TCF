#pragma once

#include <string>
#include <vector>

#include "Piece.hh"
#include "Coordinate.hh"

class King : public Piece
{
public:
    King(PieceColor pColor, Coordinate pPosition);
    ~King() override = default;

    std::string toString(bool literal = false) const override;
};