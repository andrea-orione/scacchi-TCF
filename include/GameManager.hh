#pragma once

#include <memory>
#include <string>
#include <regex>
#include <fstream>

#include "Piece.hh"

/**
 * Enumeration representing the Possible states of the game.
 *
 * Can take five values: `PLAYING`, `CHECKMATE`, `STALEMATE`, `MATERIAL_LACK` and `REPETITION`.
 */
enum class GameStatus
{
  PLAYING,
  CHECKMATE,
  STALEMATE,
  MATERIAL_LACK,
  REPETITION
};

/**
 * A class for managing the creation of the pieces,
 * the board and the user IO.
 */
class GameManager
{
public:
  GameManager();
  ~GameManager() = default;

  static std::shared_ptr<Piece> MakePiece(char pieceChar, const Coordinate pPosition, const bool hasRookMoved = true);

  void StartGame();
  void GameLoop();

private:
  static std::regex regexRuleNormal;
  static std::regex regexRulePromotion;

  PieceColor activePlayerColor;
  GameStatus gameStatus;
  bool simplified;

  std::fstream welcomeFile;
  std::fstream helpFile;
  std::fstream settingsFile;

  void LoadFenPosition(std::string &&fenString) const;
  void InitializeStartingBoard() const;
  void HelpUser();
  void UserSettings();
  void GetUserMove();
  void KillGame() const;
  void UpdateGameStatus();

#ifdef _WIN32
  constexpr static char welcomeFilePath[] = "..\\utils\\welcome.txt";
  constexpr static char helpFilePath[] = "..\\utils\\help.txt";
  constexpr static char settingsFilePath[] = "..\\utils\\settings.txt";
#else
  constexpr static char welcomeFilePath[] = "../utils/welcome.txt";
  constexpr static char helpFilePath[] = "../utils/help.txt";
  constexpr static char settingsFilePath[] = "../utils/settings.txt";
#endif
};
