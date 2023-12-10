#include "GameManager.hh"

#include "Board.hh"
#include "Bishop.hh"
#include "Pawn.hh"
#include "Piece.hh"
#include "Rook.hh"
#include "Knight.hh"
#include "King.hh"
#include "Queen.hh"
#include <cctype>
#include <stdexcept>

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
      throw std::invalid_argument("GameManager::loadFenPosition(string) Invalid string.");
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
    auto piece = makePiece(analyzingChar, pPosition);
    boardInstance.updateSquare(std::make_pair(pPosition, piece));
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
  this->loadFenPosition("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

/**
 * Function for creating the pointer to a specified piece from a string.
 *
 * @param[in] pChar The Character representing the piece.
 * @param[in] pPosition The position of the piece.
 *
 * @return The pointer to the piece that has been created created.
 */
std::shared_ptr<Piece> GameManager::makePiece(char pChar, const Coordinate &pPosition) const
{
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
    break;
  case 'R':
    return std::make_shared<Rook>(pColor, pPosition);
    break;
  case 'N':
    return std::make_shared<Knight>(pColor, pPosition);
    break;
  case 'B':
    return std::make_shared<Bishop>(pColor, pPosition);
    break;
  case 'Q':
    return std::make_shared<Queen>(pColor, pPosition);
    break;
  case 'K':
    return std::make_shared<King>(pColor, pPosition);
    break;
  default:
    throw std::invalid_argument("GameManager::makePiece(char, Coordinate) Invalid pieceString value.");
  }
}
