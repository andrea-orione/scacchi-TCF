#include "GameManager.hh"

#include <iostream>
#include <cctype>
#include <stdexcept>
#include <string>
#include <string_view>
#include <memory>
#include <map>
#include <stdexcept>

#include "Board.hh"
#include "Bishop.hh"
#include "Coordinate.hh"
#include "Pawn.hh"
#include "Piece.hh"
#include "Rook.hh"
#include "Knight.hh"
#include "King.hh"
#include "Queen.hh"
#include "VoidPiece.hh"
#include "Utils.hh"

std::regex GameManager::regexRuleNormal("[a-h]{1}[0-8]{1}[a-h]{1}[0-8]{1}");
std::regex GameManager::regexRulePromotion("[a-h]{1}[0-8]{1}[a-h]{1}[0-8]{1}[R,N,B,Q,r,n,b,q]{1}");

GameManager::GameManager() : activePlayerColor(PieceColor::WHITE), gameFinished(false), simplified(false) {}

/**
 * Function to initialize the board from a FEN string.
 *
 * @param[in] fenString The string containing the configuration to load.
 */
void GameManager::loadFenPosition(std::string &&fenString) const
{
  Board &boardInstance = Board::Instance();
  boardInstance.clearBoard();

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
      throw std::invalid_argument("GameManager::loadFenPosition(string) Invalid string formatting.");
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
      std::shared_ptr<Piece> piece = makePiece(analyzingChar, pPosition);
      if (piece->getType() == PieceType::KING)
      {
        bool &hasKingColor = (piece->getColor() == PieceColor::WHITE) ? hasWhiteKing : hasBlackKing;
        if (hasKingColor)
          throw std::invalid_argument("Too many kings");
        Coordinate &kingCoordinateColor = (piece->getColor() == PieceColor::WHITE) ? whiteKingCoordinate : blackKingCoordinate;
        hasKingColor = true;
        kingCoordinateColor = pPosition;
      }
      std::pair<Coordinate, std::shared_ptr<Piece>> p(pPosition, piece);
      boardInstance.updateSquare(std::move(p));
    }
    catch (const std::invalid_argument &e)
    {
      throw std::invalid_argument("GameManager::loadFenPosition(string) Invalid naming in FEN string.");
    }

    analyzingX++;
    analyzingPosition++;
  }
  if (!(hasBlackKing && hasWhiteKing))
    throw std::invalid_argument("GameManager::loadFenPosition(string) Not enough kings.");
  boardInstance.addKings(whiteKingCoordinate, blackKingCoordinate);

  // ActivePiece
  analyzingPosition++;
  analyzingChar = fenString.at(analyzingPosition);
  switch (analyzingChar)
  {
  case 'w':
    break;
  case 'b':
    boardInstance.incrementMoveNumber();
    break;
  default:
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
      throw std::invalid_argument("GameManager::loadFendPosition() Invalid castling section");
      break;
    }
    std::shared_ptr<Piece> rook = boardInstance.getPiece(rookPosition);
    if (rook->getType() != PieceType::ROOK)
      throw std::invalid_argument("GameManager::loadFendPosition() Invalid castling section");
    char rookChar = (rook->getColor() == PieceColor::WHITE) ? 'R' : 'r';
    std::shared_ptr<Piece> newRook = makePiece(rookChar, rookPosition, false);
    std::pair<Coordinate, std::shared_ptr<Piece>> p(rookPosition, newRook);
    boardInstance.updateSquare(std::move(p));
    analyzingPosition++;
    analyzingChar = fenString.at(analyzingPosition);
  }

  // En passant Square
  analyzingPosition++;
  const bool hasEnPassant = fenString.at(analyzingPosition) != '-';
  const Coordinate enPassantPawnPosition = (hasEnPassant) ? Coordinate(fenString.substr(analyzingPosition, 2)) : Coordinate();

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
  boardInstance.incrementMoveNumber((std::stoi(fenString.substr(analyzingPosition)) - 1) * 2);
  if (hasEnPassant)
    boardInstance.getPiece(enPassantPawnPosition)->move(enPassantPawnPosition);

  // Updating PiecesVector
  boardInstance.updatePiecesVector();
}

/**
 * Function for initializing the board at the beginning of the game.
 */
void GameManager::InitializeStartingBoard() const
{
  try
  {
    this->loadFenPosition("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << e.what() << '\n';
    throw std::runtime_error("Impossible to load the FEN string.");
  }
}

/**
 * Function for creating the pointer to a specified piece from.
 *
 * @param[in] pChar The `char` representing the piece.
 * @param[in] pPosition The position of the piece.
 * @param[in] hasMoved For king and rook, `false` by default.
 *
 * @return The pointer to the piece that has been created created.
 */
std::shared_ptr<Piece> GameManager::makePiece(char pChar, const Coordinate pPosition, const bool hasRookMoved)
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
void GameManager::startGame()
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
      gameLoop();
      break;
    }
    else if (choice == "h" || choice == "H")
    {
      utils::clear();
      helpUser();
      break;
    }
    else if (choice == "s" || choice == "S")
    {
      utils::clear();
      userSettings();
      break;
    }
    else if (choice == "e" || choice == "E")
      killGame();
    else
      continue;
  }

  InitializeStartingBoard();
}

/**
 * Function for opening the user's guide.
 */
void GameManager::helpUser()
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
    killGame();
}

/**
 * Function for opening the game settings.
 */
void GameManager::userSettings()
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
    if (choice == "simplified")
    {
      this->simplified = true;
      break;
    }
    else if (choice == "no simplified")
    {
      this->simplified = false;
      break;
    }
    else if (choice.length() == 0 || choice == "exit")
      break;
    else
      continue;
  }
}

/**
 * Function for reading moves from the user.
 *
 * It checks if the input is valid, then calls the right
 * function to execute the move.
 *
 */
void GameManager::getUserMove()
{
  std::string userMove;
  printf("Write your move: ");
  std::getline(std::cin, userMove);

  Board &board = Board::Instance();
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
    helpUser();
    throw GuideSignal();
  }
  else if (userMove == "settings" || userMove == "SETTINGS")
  {
    utils::clear();
    userSettings();
    throw SettingsSignal();
  }

  // Normal move
  if (userMove.length() == 4 && std::regex_match(userMove, regexRuleNormal))
  {
    std::string_view startingSquare(userMove.c_str(), 2);
    std::string_view endingSquare(userMove.c_str() + 2, 2);

    std::shared_ptr<Piece> pieceToMove = board.getPiece(Coordinate(startingSquare));

    if (pieceToMove->getColor() != activePlayerColor)
      throw InvalidMoveException("The piece you want to move doesn't belong to you.");

    board.normalMove(std::move(pieceToMove), Coordinate(endingSquare));
  }
  // Promotion
  else if (userMove.length() == 5 && std::regex_match(userMove, regexRulePromotion))
  {
    std::string_view startingSquare(userMove.c_str(), 2);
    std::string_view endingSquare(userMove.c_str() + 2, 2);

    std::shared_ptr<Piece> pieceToMove = board.getPiece(Coordinate(startingSquare));

    if (pieceToMove->getColor() != activePlayerColor)
      throw InvalidMoveException("The piece you want to move doesn't belong to you.");

    //! @todo PROMOTION function
  }
  else
    throw InvalidNotationException();
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
void GameManager::gameLoop()
{
  Board &board = Board::Instance();
  activePlayerColor = (board.getMoveNumber() % 2) ? PieceColor::BLACK : PieceColor::WHITE;
  utils::clear();
  std::cout << std::endl;

  while (!gameFinished)
  {
    (activePlayerColor == PieceColor::WHITE) ? board.printWhiteBoard(simplified) : board.printBlackBoard(simplified);
    try
    {
      getUserMove();
      board.incrementMoveNumber();
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
      killGame();
    }

    activePlayerColor = !activePlayerColor;
  }
}

/**
 * Function for exiting from the game.
 */
void GameManager::killGame() const
{
  printf("Goodbye. \n");
  std::exit(0);
}
