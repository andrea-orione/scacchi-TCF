#pragma once

#include <string>
#include <vector>

#include "Piece.hh"
#include "Coordinate.hh"

class Pawn : public Piece
{
public:
    Pawn(PieceColor pColor, Coordinate pPosition);

    virtual std::string toString(bool literal = false) const;

    virtual std::vector<Coordinate> listValidCoordinate() const;
};