#pragma once

#include <memory>
#include <string>
#include <regex>

#include "Piece.hh"

/**
 * A class for managing the creation of the pieces,
 * the board and the user IO.
 */
class GameManager
{
public:
    GameManager() {}
    ~GameManager() {}

    void loadFenPosition(std::string &&fenString) const;
    void InitializeStartingBoard() const;

    static std::shared_ptr<Piece> makePiece(char pieceChar, const Coordinate &pPosition, const bool hasMoved = false);

    bool getUserMove() const;

private:
    static std::regex regexRuleNormal;
    static std::regex regexRuleEnPassant;
    static std::regex regexRulePromotion;

    PieceColor activePlayerColor = PieceColor::WHITE;
};
