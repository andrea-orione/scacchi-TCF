#include "Queen.hh"

std::string Queen::toString(bool literal) const
{
    std::string pieceString;

    if (!literal)
    {
        switch (type)
        {
        case PieceColor::WHITE:
            pieceString = "♛";
            break;
        case PieceColor::BLACK:
            pieceString = "♕";
            break;
        default:
            break;
        }

        return pieceString;
    }

    switch (type)
    {
    case PieceColor::WHITE:
        pieceString = 'Q';
        break;
    case PieceColor::BLACK:
        pieceString = 'q';
        break;
    default:
        break;
    }

    return pieceString;
}

std::vector<Coordinate> Queen::listValidCoordinate() const
{
    return std::vector<Coordinate>();
}