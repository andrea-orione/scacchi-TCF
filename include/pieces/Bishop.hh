#pragma once

#include <string>
#include <vector>

#include "Piece.hh"
#include "Coordinate.hh"

class Bishop : public Piece
{
public:
    Bishop(PieceColor pColor, Coordinate pPosition);
    ~Bishop() override = default;

    std::string toString(bool literal = false) const override;
};