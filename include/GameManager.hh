#pragma once

#include <memory>
#include <fstream>

#include "BoardFactory.hh"
#include "BoardRenderer.hh"
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

  void StartGame();
  void GameLoop();

private:
  PieceColor activePlayerColor;
  GameStatus gameStatus;
  std::unique_ptr<BoardRenderer> boardRenderer;
  std::unique_ptr<BoardFactory> boardFactory;
  std::vector<std::string> PastPositions;

  std::fstream welcomeFile;
  std::fstream helpFile;
  std::fstream settingsFile;
  std::fstream endFile;

  void HelpUser();
  void UserSettings();
  void GetUserMove();
  void UpdateGameStatus();
  void KillGame() const;
  void EndGame();
};
