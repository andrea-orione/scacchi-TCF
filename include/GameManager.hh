#pragma once

#include <memory>
#include <string>
#include <regex>

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

    void loadFenPosition(std::string &&fenString) const;
    void InitializeStartingBoard() const;

    static std::shared_ptr<Piece> makePiece(char pieceChar, const Coordinate &pPosition);

    void getUserMove();

private:
    static std::regex regexRuleNormal;
    static std::regex regexRuleEnPassant;
    static std::regex regexRulePromotion;

    PieceColor activePlayerColor = PieceColor::WHITE;
};
