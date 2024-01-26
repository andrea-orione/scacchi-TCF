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
 * The core class of the program:
 *  - it starts the game;
 *  - it manages the game loop;
 *  - it manages the user IO;
 *  - it updated the status of the game;
 *  - it is responsible for terminating the game.
 */
class GameManager
{
public:
  GameManager();
  ~GameManager() = default;

  void StartGame();

private:
  PieceColor activePlayerColor;
  GameStatus gameStatus;
  std::unique_ptr<BoardRenderer> boardRenderer;
  std::unique_ptr<BoardFactory> boardFactory;
  std::vector<std::string> pastPositions;

  std::fstream welcomeFile;
  std::fstream helpFile;
  std::fstream settingsFile;
  std::fstream endFile;

  void HelpUser();
  void UserSettings();
  void GameLoop();
  void GetUserMove();
  void UpdateGameStatus();
  void KillGame() const;
  void EndGame();
};
