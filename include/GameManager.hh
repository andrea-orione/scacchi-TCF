#pragma once

#include <memory>
#include <string>
#include <vector>
#include <array>
#include <map>

#include "Piece.hh"

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

    void createWhitePieces() const;
    void createBlackPieces() const;
    void loadFenPosition(const std::string &fenString) const;

    std::shared_ptr<Piece> makePiece(const PieceType pType, const PieceColor pColor, const Coordinate &pPosition) const;
    std::shared_ptr<Piece> makePiece(char pieceChar, const Coordinate &pPosition) const;

private:
    /**
     * Structure containing the positions where to place the white pieces at the beginning of the game.
     */
    struct WhiteMap
    {
        const std::array<PieceType, 6> P_TYPE = {PieceType::PAWN,
                                                 PieceType::ROOK,
                                                 PieceType::KNIGHT,
                                                 PieceType::BISHOP,
                                                 PieceType::QUEEN,
                                                 PieceType::KING};

        std::vector<std::pair<char, int>> ROOK = {{'a', 1}, {'h', 1}};
        std::vector<std::pair<char, int>> KNIGHT = {{'b', 1}, {'g', 1}};
        std::vector<std::pair<char, int>> BISHOP = {{'c', 1}, {'f', 1}};
        std::vector<std::pair<char, int>> KING = {{'e', 1}};
        std::vector<std::pair<char, int>> QUEEN = {{'d', 1}};
        std::vector<std::pair<char, int>> PAWN = {{'a', 2}, {'b', 2}, {'c', 2}, {'d', 2}, {'e', 2}, {'f', 2}, {'g', 2}, {'h', 2}};

        std::array<std::vector<std::pair<char, int>>, 6> COORD = {PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING};
    };

    /**
     * Structure containing the positions where to place the black pieces at the beginning of the game.
     */
    struct BlackMap
    {
        const std::array<PieceType, 6> P_TYPE = {PieceType::PAWN,
                                                 PieceType::ROOK,
                                                 PieceType::KNIGHT,
                                                 PieceType::BISHOP,
                                                 PieceType::QUEEN,
                                                 PieceType::KING};

        std::vector<std::pair<char, int>> ROOK = {{'a', 8}, {'h', 8}};
        std::vector<std::pair<char, int>> KNIGHT = {{'b', 8}, {'g', 8}};
        std::vector<std::pair<char, int>> BISHOP = {{'c', 8}, {'f', 8}};
        std::vector<std::pair<char, int>> KING = {{'e', 8}};
        std::vector<std::pair<char, int>> QUEEN = {{'d', 8}};
        std::vector<std::pair<char, int>> PAWN = {{'a', 7}, {'b', 7}, {'c', 7}, {'d', 7}, {'e', 7}, {'f', 7}, {'g', 7}, {'h', 7}};

        std::array<std::vector<std::pair<char, int>>, 6> COORD = {PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING};
    };
};
