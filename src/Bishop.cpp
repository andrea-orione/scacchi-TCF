#include "Bishop.hh"

string Bishop::toString(bool literal) const
{
    string pieceString;

    if (!literal)
    {
        switch (type)
        {
        case PieceType::WHITE:
            pieceString = " ♝ ";
            break;
        case PieceType::BLACK:
            pieceString = " ♗ ";
            break;
        case PieceType::EMPTY:
            pieceString = "  ";
            break;
        default:
            break;
        }

        return pieceString;
    }

    switch (type)
    {
    case PieceType::WHITE:
        pieceString = " B ";
        break;
    case PieceType::BLACK:
        pieceString = " b ";
        break;
    case PieceType::EMPTY:
        pieceString = "  ";
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