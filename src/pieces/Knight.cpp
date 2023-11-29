#include "Knight.hh"

string Knight::toString(bool literal) const
{
    string pieceString;

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

vector<Coordinate> Knight::listValidCoordinate() const
{
    return vector<Coordinate>();
}