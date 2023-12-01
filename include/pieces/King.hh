#pragma once

#include <string>
#include <vector>

#include "Piece.hh"
#include "Coordinate.hh"

class King : public Piece
{
public:
    King(PieceColor pColor);

    virtual std::string toString(bool literal = false) const;

    virtual std::vector<Coordinate> listValidCoordinate() const;
};