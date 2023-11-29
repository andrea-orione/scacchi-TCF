#pragma once

#include <memory>
#include <vector>

#include "Board.hh"
#include "Piece.hh"
#include "Bishop.hh"

using std::make_unique;
using std::shared_ptr;
using std::vector;

enum class PieceType
{
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
};

/**
 * Abstract GameManager for the creation of the pieces.
 */
class GameManager
{
public:
    GameManager() {}
    ~GameManager() {}

    /**
     * Function for creating white pieces.
     *
     * It calls the Board (singleton) and updates its `std::map<Coordinate, Piece>`.
     */
    void createWhitePieces();

    /**
     * Function for creating black pieces.
     *
     * It calls the Board (singleton) and updates its `std::map<Coordinate, Piece>`.
     */
    void createBlackPieces();

    /**
     * Function for creating the pointer to a specified piece.
     *
     * @param[in] pType The type of the piece: `PieceType::PAWN`, `PieceType::ROOK`,
     * `PieceType::KNIGHT`, `PieceType::BISHOP`, `PieceType::QUEEN`, `PieceType::KING`.
     * @param[in] pColor The color of the piece: `PieceColor::BLACK`, `PieceColor::WHITE`.
     *
     * @return The pointer to the piece that has been created created.
     */
    shared_ptr<Piece> makePiece(PieceType pType, PieceColor pColor);
};
