#include "King.hh"

std::string King::toString(bool literal) const
{
    std::string pieceString;

    if (!literal)
    {
        switch (type)
        {
        case PieceColor::WHITE:
            pieceString = "♚";
            break;
        case PieceColor::BLACK:
            pieceString = "♔";
            break;
        default:
            break;
        }

        return pieceString;
    }

    switch (type)
    {
    case PieceColor::WHITE:
        pieceString = 'K';
        break;
    case PieceColor::BLACK:
        pieceString = 'k';
        break;
    default:
        break;
    }

    return pieceString;
}

std::vector<Coordinate> King::listValidCoordinate() const
{
    return std::vector<Coordinate>();
}