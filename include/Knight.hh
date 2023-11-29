#pragma once

#include <string>
#include <vector>

#include "Piece.hh"
#include "Coordinate.hh"

using std::string;
using std::vector;

class Knight : public Piece
{
private:
public:
    Knight(PieceColor pColor) { type = pColor; }

    virtual string toString(bool literal = false) const;

    virtual vector<Coordinate> listValidCoordinate() const;
};