#include "Rook.hh"

string Rook::toString(bool literal) const
{
    string pieceString;

    if (!literal)
    {
        switch (type)
        {
        case PieceColor::WHITE:
            pieceString = "♜";
            break;
        case PieceColor::BLACK:
            pieceString = "♖";
            break;
        default:
            break;
        }

        return pieceString;
    }

    switch (type)
    {
    case PieceColor::WHITE:
        pieceString = 'R';
        break;
    case PieceColor::BLACK:
        pieceString = 'r';
        break;
    default:
        break;
    }

    return pieceString;
}

vector<Coordinate> Rook::listValidCoordinate() const
{
    return vector<Coordinate>();
}