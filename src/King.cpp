#include "King.hh"

string King::toString(bool literal) const
{
    string pieceString;

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

vector<Coordinate> King::listValidCoordinate() const
{
    return vector<Coordinate>();
}