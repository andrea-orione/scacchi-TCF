#include "Bishop.hh"

Bishop::Bishop(PieceColor pColor)
{
    type = pColor;

    switch (type)
    {
    case PieceColor::WHITE:
        character = "♝";
        break;
    case PieceColor::BLACK:
        character = "♗";
        break;
    default:
        break;
    }

    switch (type)
    {
    case PieceColor::WHITE:
        literalCharacter = 'B';
        break;
    case PieceColor::BLACK:
        literalCharacter = 'b';
        break;
    default:
        break;
    }
}

std::string Bishop::toString(bool literal) const
{
    if (!literal)
        return character;

    return std::to_string(literalCharacter);
}

std::vector<Coordinate> Bishop::listValidCoordinate() const
{
    return std::vector<Coordinate>();
}