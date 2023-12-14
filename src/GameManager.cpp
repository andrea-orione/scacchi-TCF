#include "GameManager.hh"

#include <iostream>
#include <cctype>
#include <stdexcept>
#include <string_view>
#include <memory>
#include <map>
#include <stdexcept>

#include "Board.hh"
#include "Bishop.hh"
#include "Pawn.hh"
#include "Piece.hh"
#include "Rook.hh"
#include "Knight.hh"
#include "King.hh"
#include "Queen.hh"
#include "VoidPiece.hh"
#include "Utils.hh"

using std::cout;
using std::endl;

std::regex GameManager::regexRuleNormal("[a-h]{1}[0-8]{1}[a-h]{1}[0-8]{1}");
std::regex GameManager::regexRuleEnPassant("[a-h]{1}[0-8]{1}[a-h]{1}[0-8]{1}\\se.p.");
std::regex GameManager::regexRulePromotion("[a-h]{1}[0-8]{1}[a-h]{1}[0-8]{1}[R,N,B,Q,r,n,b,q]{1}");

/**
 * Function to Initialize the board from a FEN string
 *
 * @param[in] fenString The string containing the position to load.
 */
void GameManager::loadFenPosition(std::string &&fenString) const
{
  Board &boardInstance = Board::Instance();
  boardInstance.clearBoard();

  int analyzingPosition = 0;
  int analyzingX = 1;
  int analyzingY = 8;
  while (analyzingY != 1 || analyzingX != 9)
  {
    char analyzingChar = fenString[analyzingPosition];

    // Check if is a `/` or if it should be (if it shouldn't it will throw an error in the last part)
    if (analyzingX == 9 && analyzingChar != '/')
    {
      throw std::invalid_argument("GameManager::loadFenPosition(string) Invalid string.");
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
    Coordinate pPosition(analyzingX, analyzingY);
    std::shared_ptr<Piece> piece = makePiece(analyzingChar, pPosition);
    std::pair<Coordinate, std::shared_ptr<Piece>> p(pPosition, piece);
    boardInstance.updateSquare(std::move(p));
    boardInstance.updatePiecesVector(std::move(piece));

    analyzingX++;
    analyzingPosition++;
  }
}

/**
 * Function for initializing the board at the beginning of the game.
 */
void GameManager::InitializeStartingBoard() const
{
  try
  {
    //this->loadFenPosition("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    this->loadFenPosition("rnbqkbnr/8/8/8/8/8/8/RNBQKBNR w KQkq - 0 1");
    Board &board = Board::Instance();
    board.addKings();
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << e.what() << '\n';
    std::exit(0);
  }

  Board &boardInstance = Board::Instance();
}

/**
 * Function for creating the pointer to a specified piece from a string.
 *
 * @param[in] pChar The Character representing the piece.
 * @param[in] pPosition The position of the piece.
 *
 * @return The pointer to the piece that has been created created.
 */
std::shared_ptr<Piece> GameManager::makePiece(char pChar, const Coordinate &pPosition, const bool hasMoved)
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
    throw std::invalid_argument("GameManager::makePiece(char, Coordinate) Invalid pieceString value.");
  }

  // determine the type of the piece
  switch (pChar)
  {
  case 'P':
    return std::make_shared<Pawn>(pColor, pPosition);
  case 'R':
    return std::make_shared<Rook>(pColor, pPosition, hasMoved);
  case 'N':
    return std::make_shared<Knight>(pColor, pPosition);
  case 'B':
    return std::make_shared<Bishop>(pColor, pPosition);
  case 'Q':
    return std::make_shared<Queen>(pColor, pPosition);
  case 'K':
    return std::make_shared<King>(pColor, pPosition, hasMoved);
  default:
    throw std::invalid_argument("GameManager::makePiece(char, Coordinate) Invalid pieceString value.");
  }
}

/**
 * Function for reading moves from the user.
 *
 * It checks whether the input is valid, then calls the right
 * function to execute the move.
 */
void GameManager::getUserMove()
{
  std::string userMove;
  Board &board = Board::Instance();
  cout << "Write your move: ";
  std::getline(std::cin, userMove);

  if (userMove.length() == 4 && std::regex_match(userMove, regexRuleNormal))
  {
    cout << "Mossa normale\n";

    std::string_view startingSquare(userMove.c_str(), 2);
    std::string_view endingSquare(userMove.c_str() + 2, 2);
    cout << startingSquare << " --> " << endingSquare << "\n";

    std::shared_ptr<Piece> piece = board.getPiece(Coordinate(startingSquare));
    cout << piece->toString() << endl;
    try
    {
      board.normalMove(std::move(piece), Coordinate(endingSquare));
    }
    catch (InvalidMoveException &e)
    {
      cout << e.what() << endl;
    }
  }
  else if (userMove.length() == 9 && std::regex_match(userMove, regexRuleEnPassant))
  {
    cout << "En passant\n";

    std::string_view startingSquare(userMove.c_str(), 2);
    std::string_view endingSquare(userMove.c_str() + 2, 2);
    cout << startingSquare << " --> " << endingSquare << "\n";

    std::shared_ptr<Piece> piece = board.getPiece(Coordinate(startingSquare));
    cout << piece->toString() << endl;

    //! @todo EN PASSANT function
  }
  else if (userMove.length() == 5 && std::regex_match(userMove, regexRulePromotion))
  {
    cout << "Promozione\n";

    std::string_view startingSquare(userMove.c_str(), 2);
    std::string_view endingSquare(userMove.c_str() + 2, 2);
    cout << startingSquare << " --> " << endingSquare << "\n";

    std::shared_ptr<Piece> piece = board.getPiece(Coordinate(startingSquare));
    cout << piece->toString() << endl;

    //! @todo PROMOTION function
  }
  else
    throw InvalidNotationException();
}
