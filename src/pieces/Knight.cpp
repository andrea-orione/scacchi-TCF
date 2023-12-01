#include "Knight.hh"

std::string Knight::toString(bool literal) const
{
    std::string pieceString;

    if (!literal)
    {
        switch (type)
        {
        case PieceColor::WHITE:
            pieceString = "♞";
            break;
        case PieceColor::BLACK:
            pieceString = "♘";
            break;
        default:
            break;
        }

        return pieceString;
    }

    switch (type)
    {
    case PieceColor::WHITE:
        pieceString = 'N';
        break;
    case PieceColor::BLACK:
        pieceString = 'n';
        break;
    default:
        break;
    }

    return pieceString;
}

std::vector<Coordinate> Knight::listValidCoordinate() const
{
    return std::vector<Coordinate>();
}