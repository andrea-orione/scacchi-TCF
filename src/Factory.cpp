#include "Factory.hh"

void Factory::createWhitePieces()
{
    PieceColor pColor = PieceColor::WHITE;
    Board &boardInstance = Board::Instance();

    // bishops
    boardInstance.AddPiece(std::make_pair(Coordinate(3, 1), makePiece(PieceType::BISHOP, pColor)));
    boardInstance.AddPiece(std::make_pair(Coordinate(6, 1), makePiece(PieceType::BISHOP, pColor)));
}

void Factory::createBlackPieces()
{
    PieceColor pColor = PieceColor::BLACK;
    Board &boardInstance = Board::Instance();

    // bishops
    boardInstance.AddPiece(std::make_pair(Coordinate(3, 8), makePiece(PieceType::BISHOP, pColor)));
    boardInstance.AddPiece(std::make_pair(Coordinate(6, 8), makePiece(PieceType::BISHOP, pColor)));
}

shared_ptr<Piece> Factory::makePiece(PieceType pType, PieceColor pColor)
{

    switch (pType)
    {
    case PieceType::BISHOP:
        return std::make_shared<Bishop>(pColor);
        break;

    default:
        return nullptr;
    }
}
