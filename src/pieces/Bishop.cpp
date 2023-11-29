#include "Bishop.hh"

string Bishop::toString(bool literal) const
{
    string pieceString;

    if (!literal)
    {
        switch (type)
        {
        case PieceColor::WHITE:
            pieceString = "♝";
            break;
        case PieceColor::BLACK:
            pieceString = "♗";
            break;
        default:
            break;
        }

        return pieceString;
    }

    switch (type)
    {
    case PieceColor::WHITE:
        pieceString = 'B';
        break;
    case PieceColor::BLACK:
        pieceString = 'b';
        break;
    default:
        break;
    }

    return pieceString;
}

vector<Coordinate> Bishop::listValidCoordinate() const
{
    return vector<Coordinate>();
}