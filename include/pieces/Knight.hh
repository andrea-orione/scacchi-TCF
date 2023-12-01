#pragma once

#include <string>
#include <vector>

#include "Piece.hh"
#include "Coordinate.hh"

class Knight : public Piece
{
private:
public:
    Knight(PieceColor pColor) { type = pColor; }

    virtual std::string toString(bool literal = false) const;

    virtual std::vector<Coordinate> listValidCoordinate() const;
};