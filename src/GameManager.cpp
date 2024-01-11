#include "GameManager.hh"

#include <algorithm>
#include <array>
#include <cctype>
#include <charconv>
#include <filesystem>
#include <iostream>
#include <memory>
#include <map>
#include <regex>
#include <stdexcept>
#include <string>
#include <string_view>

#include "Bishop.hh"
#include "Board.hh"
#include "ColoredBoardRenderer.hh"
#include "Coordinate.hh"
#include "King.hh"
#include "Knight.hh"
#include "InvertedBoardRenderer.hh"
#include "NormalBoardRenderer.hh"
#include "Pawn.hh"
#include "Piece.hh"
#include "Queen.hh"
#include "Rook.hh"
#include "SimplifiedBoardRenderer.hh"
#include "Utils.hh"
#include "VoidPiece.hh"

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
                             boardRenderer(std::make_unique<NormalBoardRenderer>())
{}

/**
 * Function for creating the pointer to a specified piece from.
 *
 * @param[in] pChar The `char` representing the piece.
 * @param[in] pPosition The position of the piece.
 * @param[in] hasMoved For king and rook, `false` by default.
 *
 * @return The pointer to the piece that has been created created.
 */
std::shared_ptr<Piece> GameManager::MakePiece(char pChar, const Coordinate pPosition, const bool hasRookMoved)
{
  // Check if void
  if (pChar == 0)
    return std::make_shared<VoidPiece>(pPosition);

  // determine the color of the piece
  PieceColor pColor;
  if (std::isupper(pChar))
  {
    pColor = PieceColor::WHITE;
  }
  else if (std::islower(pChar))
  {
    pColor = PieceColor::BLACK;
    pChar = std::toupper(pChar);
  }
  else
  {
    throw std::invalid_argument("GameManager::makePiece(char, Coordinate) Invalid value for char representing piece.");
  }

  // determine the type of the piece
  switch (pChar)
  {
  case 'P':
    return std::make_shared<Pawn>(pColor, pPosition);
  case 'R':
    return std::make_shared<Rook>(pColor, pPosition, hasRookMoved);
  case 'N':
    return std::make_shared<Knight>(pColor, pPosition);
  case 'B':
    return std::make_shared<Bishop>(pColor, pPosition);
  case 'Q':
    return std::make_shared<Queen>(pColor, pPosition);
  case 'K':
    return std::make_shared<King>(pColor, pPosition, false);
  default:
    throw std::invalid_argument("GameManager::makePiece(char, Coordinate) Invalid value for char representing piece.");
  }
}

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
      InitializeStartingBoard();
      GameLoop();
      break;
    }
    else if (choice == "h" || choice == "H")
    {
      utils::clear();
      HelpUser();
      InitializeStartingBoard();
      GameLoop();
      break;
    }
    else if (choice == "s" || choice == "S")
    {
      utils::clear();
      UserSettings();
      InitializeStartingBoard();
      GameLoop();
      break;
    }
    else if (choice == "e" || choice == "E")
      KillGame();
    else
      continue;
  }

  InitializeStartingBoard();
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
 * Function to initialize the board from a FEN string.
 *
 * It first analyzes the first part of the string containing the position of all
 * the pieces and updates the board
 *
 * @param[in] fenString The string containing the configuration to load.
 */
void GameManager::LoadFenPosition(std::string_view fenString) const
{
  Board &boardInstance = Board::Instance();
  boardInstance.ClearBoard();

  bool hasWhiteKing = false;
  bool hasBlackKing = false;
  Coordinate whiteKingCoordinate(1, 1);
  Coordinate blackKingCoordinate(1, 1);
  int analyzingPosition = 0;
  int analyzingX = 1;
  int analyzingY = 8;
  char analyzingChar;
  while (analyzingY != 1 || analyzingX != 9)
  {
    analyzingChar = fenString.at(analyzingPosition);

    // Check if is a `/` or if it should be (if it shouldn't it will throw an error in the last part)
    if (analyzingX == 9 && analyzingChar != '/')
    {
      boardInstance.ClearBoard();
      throw std::invalid_argument("GameManager::loadFenPosition(string) Invalid string formatting.");
    }
    if (analyzingX == 9 && analyzingChar == '/')
    {
      analyzingX = 1;
      analyzingY--;
      analyzingPosition++;
      continue;
    }

    // Check if is a number
    int numericValue = analyzingChar - '0'; // Uses numeric memory representation of char trick.
    if (numericValue > 0 && numericValue + analyzingX < 10)
    {
      analyzingX += numericValue;
      analyzingPosition++;
      continue;
    }

    // Insert the piece. makePiece should handle the errors
    try
    {
      Coordinate pPosition(analyzingX, analyzingY);
      std::shared_ptr<Piece> piece = MakePiece(analyzingChar, pPosition);
      if (piece->GetType() == PieceType::KING)
      {
        bool &hasKingColor = (piece->GetColor() == PieceColor::WHITE) ? hasWhiteKing : hasBlackKing;
        if (hasKingColor)
          throw std::invalid_argument("Too many kings");
        Coordinate &kingCoordinateColor = (piece->GetColor() == PieceColor::WHITE) ? whiteKingCoordinate : blackKingCoordinate;
        hasKingColor = true;
        kingCoordinateColor = pPosition;
      }
      std::pair<Coordinate, std::shared_ptr<Piece>> p(pPosition, piece);
      boardInstance.UpdateSquare(p);
    }
    catch (const std::invalid_argument &e)
    {
      boardInstance.ClearBoard();
      throw std::invalid_argument("GameManager::loadFenPosition(string) Invalid naming in FEN string.");
    }

    analyzingX++;
    analyzingPosition++;
  }
  if (!(hasBlackKing && hasWhiteKing))
  {
    boardInstance.ClearBoard();
    throw std::invalid_argument("GameManager::loadFenPosition(string) Not enough kings.");
  }
  boardInstance.AddKings(whiteKingCoordinate, blackKingCoordinate);

  // ActivePiece
  analyzingPosition++;
  analyzingChar = fenString.at(analyzingPosition);
  switch (analyzingChar)
  {
    case 'w':
      break;
    case 'b':
      boardInstance.IncrementMoveNumber();
      break;
    default:
      boardInstance.ClearBoard();
      throw std::invalid_argument("GameManager::loadFenPosition(string) Invalid active color");
  }

  // Castling availability
  analyzingPosition += 2;
  if (fenString.at(analyzingPosition) == '-')
    analyzingPosition++;
  analyzingChar = fenString.at(analyzingPosition);
  while (analyzingChar != ' ')
  {
    Coordinate rookPosition;
    switch (analyzingChar)
    {
      case 'K':
        rookPosition = Coordinate(8, 1);
        break;
      case 'Q':
        rookPosition = Coordinate(1, 1);
        break;
      case 'k':
        rookPosition = Coordinate(8, 8);
        break;
      case 'q':
        rookPosition = Coordinate(1, 8);
        break;
      default:
        boardInstance.ClearBoard();
        throw std::invalid_argument("GameManager::loadFendPosition() Invalid castling section");
        break;
    }
    std::shared_ptr<Piece> rook = boardInstance.GetPiece(rookPosition);
    if (rook->GetType() != PieceType::ROOK)
    {
      boardInstance.ClearBoard();
      throw std::invalid_argument("GameManager::loadFendPosition() Invalid castling section");
    }
    char rookChar = (rook->GetColor() == PieceColor::WHITE) ? 'R' : 'r';
    std::shared_ptr<Piece> newRook = MakePiece(rookChar, rookPosition, false);
    std::pair<Coordinate, std::shared_ptr<Piece>> p(rookPosition, newRook);
    boardInstance.UpdateSquare(p);
    analyzingPosition++;
    analyzingChar = fenString.at(analyzingPosition);
  }

  // En passant Substring
  analyzingPosition++;
  const bool hasEnPassant = fenString.at(analyzingPosition) != '-';
  const std::string_view enPassantSubstring = (hasEnPassant) ? fenString.substr(analyzingPosition, 2) : "";

  // Half move number (useless)
  analyzingPosition += 2;
  analyzingChar = fenString.at(analyzingPosition);
  while (analyzingChar != ' ')
  {
    analyzingPosition++;
    analyzingChar = fenString.at(analyzingPosition);
  }

  // moveNumber
  analyzingPosition++;
  std::string_view sMoveNumber = fenString.substr(analyzingPosition);
  int iMoveNumber;
  std::from_chars(sMoveNumber.data(), sMoveNumber.data() + sMoveNumber.size(), iMoveNumber);
  boardInstance.IncrementMoveNumber((iMoveNumber - 1) * 2);

  // enPassant
  if (hasEnPassant)
  {
    try
    {
      const Coordinate enPassantPawnPosition = Coordinate(enPassantSubstring);
      boardInstance.GetPiece(enPassantPawnPosition)->Move(enPassantPawnPosition);
    }
    catch (std::invalid_argument)
    {
      boardInstance.ClearBoard();
      throw std::invalid_argument("GameManager::loadFendPosition() Invalid en-passant section");
    }
  }

  // Updating PiecesVector
  boardInstance.UpdatePiecesVector();
}

/**
 * Function for initializing the board at the beginning of the game.
 */
void GameManager::InitializeStartingBoard() const
{
  try
  {
    //! @todo Delete test FENs
    this->LoadFenPosition("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    // this->LoadFenPosition("r1bqkbnr/pPpppppp/8/8/8/8/P1PPPPPP/RNBQKBNR w KQkq - 0 1");
    // this->LoadFenPosition("2n1n3/3PK1kp/8/8/8/8/8/8 w - - 0 1");
    // this->LoadFenPosition("8/3PK1kp/8/8/8/8/8/8 w - - 0 1");
    // this->LoadFenPosition("k7/3R4/7Q/8/8/8/8/7K w - - 0 1");
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << e.what() << '\n';
    throw std::runtime_error("Impossible to load the FEN string.");
  }
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
    std::string_view startingSquare(userMove.c_str(), 2);
    std::string_view endingSquare(userMove.c_str() + 2, 2);

    std::shared_ptr<Piece> pieceToMove = board.GetPiece(Coordinate(startingSquare));

    if (pieceToMove->GetColor() != activePlayerColor)
      throw InvalidMoveException("The piece you want to move doesn't belong to you.");

    // check for trying to move pawn without promoting
    if (pieceToMove->GetDoubleAdvancementMoveNumber())
    {
      if ((startingSquare[1] == '7' && endingSquare[1] == '8') || (startingSquare[1] == '2' && endingSquare[1] == '1'))
        throw InvalidMoveException("You have to promote this pawn.");
    }

    board.NormalMove(std::move(pieceToMove), Coordinate(endingSquare));
    UpdateGameStatus();
  }
  // Promotion
  else if (userMove.length() == 5 && std::regex_match(userMove, regexRulePromotion))
  {
    std::string_view startingSquare(userMove.c_str(), 2);
    std::string_view endingSquare(userMove.c_str() + 2, 2);
    char promotionPiece = userMove[4];

    std::shared_ptr<Piece> pieceToMove = board.GetPiece(Coordinate(startingSquare));

    if (pieceToMove->GetColor() != activePlayerColor)
      throw InvalidMoveException("The piece you want to move doesn't belong to you.");

    if (!pieceToMove->GetDoubleAdvancementMoveNumber())
      throw InvalidMoveException("You cannot promote a piece which is not a pawn.");

    board.Promotion(std::move(pieceToMove), promotionPiece, Coordinate(endingSquare));
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
