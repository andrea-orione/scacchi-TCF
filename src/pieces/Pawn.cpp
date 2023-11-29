#include "Pawn.hh"

string Pawn::toString(bool literal) const
{
    string pieceString;

    if (!literal)
    {
        switch (type)
        {
        case PieceColor::WHITE:
            pieceString = "♟︎";
            break;
        case PieceColor::BLACK:
            pieceString = "♙";
            break;
        default:
            break;
        }

        return pieceString;
    }

    switch (type)
    {
    case PieceColor::WHITE:
        pieceString = 'P';
        break;
    case PieceColor::BLACK:
        pieceString = 'p';
        break;
    default:
        break;
    }

    return pieceString;
}

vector<Coordinate> Pawn::listValidCoordinate() const
{
    return vector<Coordinate>();
}