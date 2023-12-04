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

    std::vector<Coordinate> listValidCoordinate() const override;
};