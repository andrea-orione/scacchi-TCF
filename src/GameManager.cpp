#include "GameManager.hh"

#include <algorithm>
#include <array>
#include <filesystem>
#include <iostream>
#include <memory>
#include <map>
#include <regex>
#include <stdexcept>
#include <string>
#include <string_view>

#include "Board.hh"
#include "BoardFactory.hh"
#include "CastlingMover.hh"
#include "ColoredBoardRenderer.hh"
#include "Coordinate.hh"
#include "EnPassantMover.hh"
#include "InvertedBoardRenderer.hh"
#include "NormalBoardRenderer.hh"
#include "NormalMover.hh"
#include "Piece.hh"
#include "PieceMover.hh"
#include "PromotionMover.hh"
#include "SimplifiedBoardRenderer.hh"
#include "Utils.hh"

const std::regex regexRuleNormal{"[a-h][1-8][a-h][1-8]"};
const std::regex regexRulePromotion{"[a-h][2,7][a-h][1,8][R,N,B,Q,r,n,b,q]"};

const std::filesystem::path welcomeFilePath{"../utils/welcome.txt"};
const std::filesystem::path helpFilePath{"../utils/help.txt"};
const std::filesystem::path settingsFilePath{"../utils/settings.txt"};
std::string endGameDirPath = "../utils/end_game/";

const std::map<GameStatus, const char *> endgameFilesMap = {
  {GameStatus::CHECKMATE, "checkmate.txt"},
  {GameStatus::STALEMATE, "stalemate.txt"},
  {GameStatus::MATERIAL_LACK, "material.txt"},
  {GameStatus::REPETITION, "repetition.txt"}};

constexpr std::array<const char *, 4> settings = {"normal", "simplified", "colored", "inverted"};

GameManager::GameManager() : activePlayerColor(PieceColor::WHITE),
                             gameStatus(GameStatus::PLAYING),
                             boardFactory(BoardFactory()),
                             boardRenderer(std::make_unique<NormalBoardRenderer>())
{}

/**
 * Function for initializing the game.
 */
void GameManager::StartGame()
{
  // open file with welcome text
  welcomeFile.open(welcomeFilePath, std::ios::in);

  if (!welcomeFile.is_open())
    throw std::runtime_error("Error opening welcome.txt");

  // read from file
  utils::clear();
  std::string line;
  while (std::getline(welcomeFile, line))
    printf("%s\n", line.c_str());
  welcomeFile.close();

  // user option
  std::string choice;
  while (true)
  {
    printf("Option: ");
    std::getline(std::cin, choice);
    if (choice == "g" || choice == "G")
    {
      boardFactory.InitializeStartingBoard();
      GameLoop();
      break;
    }
    else if (choice == "h" || choice == "H")
    {
      utils::clear();
      HelpUser();
      boardFactory.InitializeStartingBoard();
      GameLoop();
      break;
    }
    else if (choice == "s" || choice == "S")
    {
      utils::clear();
      UserSettings();
      boardFactory.InitializeStartingBoard();
      GameLoop();
      break;
    }
    else if (choice == "e" || choice == "E")
      KillGame();
    else
      continue;
  }

  boardFactory.InitializeStartingBoard();
}

/**
 * The most important function of the `GameManager`.
 *
 * It creates the game loop, thereby allowing the users to
 * play continuously until the game is finished.
 *
 * It is responsible of printing the updated board at
 * the beginning of each player's turn.
 */
void GameManager::GameLoop()
{
  Board &board = Board::Instance();
  activePlayerColor = (board.GetMoveNumber() % 2) ? PieceColor::BLACK : PieceColor::WHITE;
  utils::clear();
  std::cout << std::endl;

  while (gameStatus == GameStatus::PLAYING)
  {
    boardRenderer->PrintBoard(activePlayerColor);
    try
    {
      GetUserMove();
      board.IncrementMoveNumber();
      utils::clear();
      std::cout << std::endl;
    }
    catch (GuideSignal)
    {
      utils::clear();
      continue;
    }
    catch (SettingsSignal)
    {
      utils::clear();
      continue;
    }
    catch (InvalidMoveException &e)
    {
      utils::clear();
      std::cerr << e.what() << '\n';
      continue;
    }
    catch (InvalidNotationException &e)
    {
      utils::clear();
      std::cerr << e.what() << '\n';
      continue;
    }
    catch (const std::runtime_error &e)
    {
      utils::clear();
      std::cerr << e.what() << '\n';
      KillGame();
    }

    activePlayerColor = !activePlayerColor;
  }

  EndGame();
}

/**
 * Function for opening the user's guide.
 */
void GameManager::HelpUser()
{
  helpFile.open(helpFilePath, std::ios::in);

  if (!helpFile.is_open())
    throw std::runtime_error("Error opening help.txt");

  std::string line;
  while (std::getline(helpFile, line))
    printf("%s\n", line.c_str());
  helpFile.close();

  printf("\nType 'e' or 'E' to exit, any other character to start the game: ");
  std::string choice;
  std::getline(std::cin, choice);
  if (choice == "e" || choice == "E")
    KillGame();
}

/**
 * Function for opening the game settings.
 */
void GameManager::UserSettings()
{
  settingsFile.open(settingsFilePath, std::ios::in);

  if (!settingsFile.is_open())
    throw std::runtime_error("Error opening settings.txt");

  std::string line;
  while (std::getline(settingsFile, line))
    printf("%s\n", line.c_str());
  settingsFile.close();

  std::string choice;
  while (true)
  {
    printf("\nOption: ");
    std::getline(std::cin, choice);

    if (choice.length() == 0 || choice == "exit")
      break;

    auto itr = std::find(settings.begin(), settings.end(), choice);
    if (itr == settings.end())
      continue;

    size_t index = std::distance(settings.begin(), itr);
    printf("%i\n", (int)index);

    switch (index)
    {
    case 0:
      this->boardRenderer = std::make_unique<NormalBoardRenderer>();
      break;
    case 1:
      this->boardRenderer = std::make_unique<SimplifiedBoardRenderer>();
      break;
    case 2:
      this->boardRenderer = std::make_unique<ColoredBoardRenderer>();
      break;
    case 3:
      this->boardRenderer = std::make_unique<InvertedBoardRenderer>();
      break;
    }

    break;
  }
}

/**
 * Function for reading moves from the user.
 *
 * It checks if the input is valid, then calls the right
 * function to execute the move.
 *
 */
void GameManager::GetUserMove()
{
  std::string userMove;
  printf("Write your move: ");
  std::getline(std::cin, userMove);

  if (userMove == "exit" || userMove == "EXIT")
  {
    char exitChar;
    printf("Are you sure you want to exit? (y/n) ");
    std::cin >> exitChar;

    if (exitChar == 'y' || exitChar == 'Y')
      throw std::runtime_error("Exiting the game.");
  }
  else if (userMove == "guide" || userMove == "GUIDE")
  {
    utils::clear();
    HelpUser();
    throw GuideSignal();
  }
  else if (userMove == "settings" || userMove == "SETTINGS")
  {
    utils::clear();
    UserSettings();
    throw SettingsSignal();
  }

  // Normal move
  Board &board = Board::Instance();
  if (userMove.length() == 4 && std::regex_match(userMove, regexRuleNormal))
  {
    const Coordinate startingSquare(std::string_view(userMove.c_str(), 2));
    const Coordinate endingSquare(std::string_view(userMove.c_str() + 2, 2));

    std::shared_ptr<Piece> pieceToMove = board.GetPiece(startingSquare);

    if (pieceToMove->GetColor() != activePlayerColor)
      throw InvalidMoveException("The piece you want to move doesn't belong to you.");

    // check for trying to move pawn without promoting
    MoveType moveType = pieceToMove->IsMoveValid(Coordinate(endingSquare));
    std::unique_ptr<PieceMover> moveHandler;
    switch (moveType)
    {
      case MoveType::NORMAL:
        moveHandler = std::make_unique<NormalMover>();
        break;
      case MoveType::ENPASSANT:
        moveHandler = std::make_unique<EnPassantMover>();
        break;
      case MoveType::CASTLING:
        moveHandler = std::make_unique<CastlingMover>();
        break;
      case MoveType::PROMOTION:
        throw InvalidMoveException("You have to promote this pawn.");
        break;
      case MoveType::INVALID:
        throw InvalidMoveException("This move is not allowed. This piece cannot reach that position.");
        break;
    }
    moveHandler->Move(std::move(pieceToMove), endingSquare);
    UpdateGameStatus();
  }

  // Promotion
  else if (userMove.length() == 5 && std::regex_match(userMove, regexRulePromotion))
  {
    const Coordinate startingSquare(std::string_view(userMove.c_str(), 2));
    const Coordinate endingSquare(std::string_view(userMove.c_str() + 2, 2));
    const char promotionPiece = userMove[4];

    std::shared_ptr<Piece> pieceToMove = board.GetPiece(Coordinate(startingSquare));

    if (pieceToMove->GetColor() != activePlayerColor)
      throw InvalidMoveException("The piece you want to move doesn't belong to you.");

    if (pieceToMove->GetType() != PieceType::PAWN)
      throw InvalidMoveException("You cannot promote a piece which is not a pawn.");

    MoveType moveType = pieceToMove->IsMoveValid(Coordinate(endingSquare));
    if (moveType == MoveType::INVALID)
      throw InvalidMoveException("This move is not allowed. This piece cannot reach that position.");

    const auto moveHandler = std::make_unique<PromotionMover>(promotionPiece);
    moveHandler->Move(std::move(pieceToMove), endingSquare);
    UpdateGameStatus();
  }
  else
    throw InvalidNotationException();
}

/**
 * Function to evaluate if the game status.
 *
 * It checks if there are enough pieces, if is checkmate or stalemate or if it
 * is draw by repetition. Based on that it updates the gameStatus variable.
 */
void GameManager::UpdateGameStatus()
{
  Board &board = Board::Instance();
  if (!board.HasValidMoves(!activePlayerColor))
  {
    if (board.IsKingInCheck(!activePlayerColor))
    {
      gameStatus = GameStatus::CHECKMATE;
      return;
    }
    gameStatus = GameStatus::STALEMATE;
    return;
  }

  if (board.IsMaterialLacking())
  {
    gameStatus = GameStatus::MATERIAL_LACK;
    return;
  }
}

/**
 * Function for ending the game.
 */
void GameManager::EndGame()
{
  boardRenderer->PrintBoard(!activePlayerColor);

  endFile.open(std::filesystem::path{endGameDirPath + endgameFilesMap.at(gameStatus)}, std::ios::in);
  if (!endFile.is_open())
    throw std::runtime_error("Impossible to open endgame text file.");

  std::string line;
  while (std::getline(endFile, line))
    printf("%s\n", line.c_str());

  endFile.close();

  if (gameStatus == GameStatus::CHECKMATE)
  {
    const char *winner = (!activePlayerColor == PieceColor::BLACK) ? "BLACK" : "WHITE";
    printf("\n                           %s WON!\n", winner);
  }
  printf("\nPress 'Enter' to exit.\n");
  std::cin.get();
}

/**
 * Function for exiting from the game.
 */
void GameManager::KillGame() const
{
  printf("Goodbye. \n");
  std::exit(0);
}
