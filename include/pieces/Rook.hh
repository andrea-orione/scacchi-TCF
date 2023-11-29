#pragma once

#include <string>
#include <vector>

#include "Piece.hh"
#include "Coordinate.hh"

using std::string;
using std::vector;

class Rook : public Piece
{
private:
public:
    Rook(PieceColor pColor) { type = pColor; }

    virtual string toString(bool literal = false) const;

    virtual vector<Coordinate> listValidCoordinate() const;
};