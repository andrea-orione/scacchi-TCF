#include "GameManager.hh"

#include "Board.hh"
#include "Bishop.hh"
#include "Pawn.hh"
#include "Rook.hh"
#include "Knight.hh"
#include "King.hh"
#include "Queen.hh"

/**
 * Function for creating white pieces.
 *
 * It calls the Board (singleton) and updates its `std::map<Coordinate, Piece>`.
 */
void GameManager::createWhitePieces()
{
    PieceColor pColor = PieceColor::WHITE;
    Board &boardInstance = Board::Instance();

    // get map of white pieces coordinates
    std::unique_ptr<WhiteMap> wm = std::make_unique<WhiteMap>();

    for (PieceType pt : wm->P_TYPE)
    {
        // explicitly convert PieceType to int
        int i = static_cast<std::underlying_type_t<PieceType>>(pt);

        for (std::pair<char, int> xy : wm->COORD[i])
        {
            boardInstance.UpdateSquare(std::make_pair(Coordinate(xy.first, xy.second), makePiece(pt, pColor)));
        }
    }
}

/**
 * Function for creating black pieces.
 *
 * It calls the Board (singleton) and updates its `std::map<Coordinate, Piece>`.
 */
void GameManager::createBlackPieces()
{
    PieceColor pColor = PieceColor::BLACK;
    Board &boardInstance = Board::Instance();

    // get map of black pieces coordinates
    std::unique_ptr<BlackMap> wm = std::make_unique<BlackMap>();

    for (PieceType pt : wm->P_TYPE)
    {
        // explicitly convert PieceType to int
        int i = static_cast<std::underlying_type_t<PieceType>>(pt);

        for (std::pair<char, int> xy : wm->COORD[i])
        {
            boardInstance.UpdateSquare(std::make_pair(Coordinate(xy.first, xy.second), makePiece(pt, pColor)));
        }
    }
}

/**
 * Function for creating the pointer to a specified piece.
 *
 * @param[in] pType The type of the piece: `PieceType::PAWN`, `PieceType::ROOK`,
 * `PieceType::KNIGHT`, `PieceType::BISHOP`, `PieceType::QUEEN`, `PieceType::KING`.
 * @param[in] pColor The color of the piece: `PieceColor::BLACK`, `PieceColor::WHITE`.
 *
 * @return The pointer to the piece that has been created created.
 */
std::shared_ptr<Piece> GameManager::makePiece(PieceType pType, PieceColor pColor)
{

    switch (pType)
    {
    case PieceType::PAWN:
        return std::make_shared<Pawn>(pColor);
        break;
    case PieceType::ROOK:
        return std::make_shared<Rook>(pColor);
        break;
    case PieceType::KNIGHT:
        return std::make_shared<Knight>(pColor);
        break;
    case PieceType::BISHOP:
        return std::make_shared<Bishop>(pColor);
        break;
    case PieceType::QUEEN:
        return std::make_shared<Queen>(pColor);
        break;
    case PieceType::KING:
        return std::make_shared<King>(pColor);
        break;

    default:
        return nullptr;
    }
}
