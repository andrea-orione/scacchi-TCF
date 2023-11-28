#pragma once

#include <string>
#include <vector>

#include "Piece.hh"
#include "Coordinate.hh"

using std::string;
using std::vector;

class Bishop : public Piece
{
private:
public:
    Bishop(PieceType pType) { type = pType; }

    virtual string toString(bool literal = false) const;

    virtual vector<Coordinate> listValidCoordinate() const;
};