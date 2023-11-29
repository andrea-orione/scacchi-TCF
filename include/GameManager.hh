#pragma once

#include <memory>
#include <vector>
#include <array>
#include <map>
#include <utility>

#include "Board.hh"
#include "Piece.hh"
#include "Bishop.hh"

using std::array;
using std::map;
using std::pair;
using std::shared_ptr;
using std::unique_ptr;
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

private:
    /**
     * Structure containing the positions where to place the white pieces at the beginning of the game.
     */
    struct WhiteMap
    {
        const array<PieceType, 6> P_TYPE = {PieceType::PAWN, PieceType::ROOK, PieceType::KNIGHT, PieceType::BISHOP, PieceType::QUEEN, PieceType::KING};

        vector<array<int, 2>> ROOK = {{1, 1}, {8, 1}};
        vector<array<int, 2>> KNIGHT = {{2, 1}, {7, 1}};
        vector<array<int, 2>> BISHOP = {{3, 1}, {6, 1}};
        vector<array<int, 2>> KING = {{4, 1}};
        vector<array<int, 2>> QUEEN = {{5, 1}};
        vector<array<int, 2>> PAWN = {{1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2}, {8, 2}};

        array<vector<array<int, 2>>, 6> COORD = {ROOK, KNIGHT, BISHOP, KING, QUEEN, PAWN};
    };

    /**
     * Structure containing the positions where to place the black pieces at the beginning of the game.
     */
    struct BlackMap
    {
        const array<PieceType, 6> P_TYPE = {PieceType::PAWN, PieceType::ROOK, PieceType::KNIGHT, PieceType::BISHOP, PieceType::QUEEN, PieceType::KING};

        vector<array<int, 2>> ROOK = {{1, 8}, {8, 8}};
        vector<array<int, 2>> KNIGHT = {{2, 8}, {7, 8}};
        vector<array<int, 2>> BISHOP = {{3, 8}, {6, 8}};
        vector<array<int, 2>> KING = {{4, 8}};
        vector<array<int, 2>> QUEEN = {{5, 8}};
        vector<array<int, 2>> PAWN = {{1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}, {6, 7}, {7, 7}, {8, 7}};

        array<vector<array<int, 2>>, 6> COORD = {ROOK, KNIGHT, BISHOP, KING, QUEEN, PAWN};
    };
};
