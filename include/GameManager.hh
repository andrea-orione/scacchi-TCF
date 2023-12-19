#pragma once

#include <memory>
#include <string>
#include <regex>
#include <fstream>

#include "Piece.hh"

/**
 * A class for managing the creation of the pieces,
 * the board and the user IO.
 */
class GameManager
{
public:
    GameManager();
    ~GameManager() = default;

    void loadFenPosition(std::string &&fenString) const;
    void InitializeStartingBoard() const;

    static std::shared_ptr<Piece> makePiece(char pieceChar, const Coordinate pPosition, const bool hasRookMoved = true);

    void startGame();
    void helpUser();
    void userSettings();
    void getUserMove();
    void gameLoop();
    void killGame() const;

private:
    static std::regex regexRuleNormal;
    static std::regex regexRulePromotion;

    PieceColor activePlayerColor;
    bool gameFinished;
    bool simplified;

    std::fstream welcomeFile;
    std::fstream helpFile;
    std::fstream settingsFile;
};
