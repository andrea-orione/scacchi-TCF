#include "GameManager.hh"

void GameManager::createWhitePieces()
{
    PieceColor pColor = PieceColor::WHITE;
    Board &boardInstance = Board::Instance();

    // get map of white pieces coordinates
    unique_ptr<WhiteMap> wm = std::make_unique<WhiteMap>();

    for (PieceType pt : wm->P_TYPE)
    {
        // explicitly convert PieceType to int
        int i = static_cast<std::underlying_type_t<PieceType>>(pt);

        for (array<int, 2> xy : wm->COORD[i])
        {
            boardInstance.AddPiece(std::make_pair(Coordinate(xy[0], xy[1]), makePiece(pt, pColor)));
        }
    }
}

void GameManager::createBlackPieces()
{
    PieceColor pColor = PieceColor::BLACK;
    Board &boardInstance = Board::Instance();

    // get map of black pieces coordinates
    unique_ptr<BlackMap> wm = std::make_unique<BlackMap>();

    for (PieceType pt : wm->P_TYPE)
    {
        // explicitly convert PieceType to int
        int i = static_cast<std::underlying_type_t<PieceType>>(pt);

        for (array<int, 2> xy : wm->COORD[i])
        {
            boardInstance.AddPiece(std::make_pair(Coordinate(xy[0], xy[1]), makePiece(pt, pColor)));
        }
    }
}

shared_ptr<Piece> GameManager::makePiece(PieceType pType, PieceColor pColor)
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
