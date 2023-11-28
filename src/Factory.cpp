#include "Factory.hh"

vector<unique_ptr<Piece>> WhiteFactory::createPieces()
{
    vector<unique_ptr<Piece>> pieces;

    // bishop
    pieces.push_back(make_unique<Bishop>(PieceType::WHITE));

    return pieces;
}

vector<unique_ptr<Piece>> BlackFactory::createPieces()
{
    vector<unique_ptr<Piece>> pieces;

    // bishop
    pieces.push_back(make_unique<Bishop>(PieceType::BLACK));

    return pieces;
}

vector<unique_ptr<Piece>> EmptyFactory::createPieces()
{
    return vector<unique_ptr<Piece>>();
}
