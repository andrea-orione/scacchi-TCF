#pragma once

#include <memory>
#include <string>
#include <regex>
#include <fstream>
#include <filesystem>

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

  static std::shared_ptr<Piece> MakePiece(char pieceChar, Coordinate pPosition, bool hasRookMoved = true);

  void StartGame();
  void GameLoop();

private:
  PieceColor activePlayerColor;
  GameStatus gameStatus;
  bool simplified;
  bool colored;

  std::fstream welcomeFile;
  std::fstream helpFile;
  std::fstream settingsFile;
  std::fstream endFile;

  void LoadFenPosition(std::string_view fenString) const;
  void InitializeStartingBoard() const;
  void HelpUser();
  void UserSettings();
  void GetUserMove();
  void UpdateGameStatus();
  void KillGame() const;
  void EndGame();
};
