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

    shared_ptr<Piece> makePiece(PieceType pType, PieceColor pColor);
};
