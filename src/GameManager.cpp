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
 * Function for creating white pieces.
 *
 * It calls the Board (singleton) and updates its `std::map<Coordinate, Piece>`.
 */
void GameManager::createWhitePieces() const
{
  constexpr PieceColor pColor = PieceColor::WHITE;
  Board &boardInstance = Board::Instance();

  // get map of white pieces coordinates
  std::unique_ptr<WhiteMap> wm = std::make_unique<WhiteMap>();

  for (PieceType pt : wm->P_TYPE)
  {
    // explicitly convert PieceType to int
    int i = static_cast<std::underlying_type_t<PieceType>>(pt);

    for (std::pair<char, int> xy : wm->COORD[i])
    {
      Coordinate pPosition(xy.first, xy.second);
      auto piece = makePiece(pt, pColor, pPosition);
      boardInstance.updateSquare(std::make_pair(pPosition, piece));
      boardInstance.updateWhitePiecesVector(piece);
    }
  }
}

/**
 * Function for creating black pieces.
 *
 * It calls the Board (singleton) and updates its `std::map<Coordinate, Piece>`.
 */
void GameManager::createBlackPieces() const
{
  constexpr PieceColor pColor = PieceColor::BLACK;
  Board &boardInstance = Board::Instance();

  // get map of black pieces coordinates
  std::unique_ptr<BlackMap> wm = std::make_unique<BlackMap>();

  for (PieceType pt : wm->P_TYPE)
  {
    // explicitly convert PieceType to int
    int i = static_cast<std::underlying_type_t<PieceType>>(pt);

    for (std::pair<char, int> xy : wm->COORD[i])
    {
      Coordinate pPosition(xy.first, xy.second);
      auto piece = makePiece(pt, pColor, pPosition);
      boardInstance.updateSquare(std::make_pair(pPosition, piece));
      boardInstance.updateBlackPiecesVector(piece);
    }
  }
}

/**
 * Function to Initialize the board from a FEN string
 *
 * @param[in] fenString The string containing the position to load.
 */
void GameManager::loadFenPosition(const std::string &fenString) const
{
  Board &boardInstance = Board::Instance();
  boardInstance.clearBoard();

  int analyzingPosition = 0;
  int analyzingX = 1;
  int analyzingY = 8;
  while (analyzingY != 1 || analyzingX != 9) {
    char analyzingChar = fenString[analyzingPosition];

    // Check if is a `/` or if should be (if it shouldnt it will throw an erron in the last part)
    if (analyzingX == 9 && analyzingChar != '/') throw std::invalid_argument("GameManager::loadFenPosition(string) Invalid string."); 
    if (analyzingX == 9 && analyzingChar == '/') {
      analyzingX = 1;
      analyzingY--;
      analyzingPosition++;
      continue;
    }

    // Check if is a number
    int numericValue = analyzingChar - '0'; // Uses numeric memory representation of char trick.
    if (numericValue>0 && numericValue+analyzingX<10) {
      analyzingX += numericValue;
      analyzingPosition++;
      continue;
    }

    // Insert the piece. makePiece should handle the errors
    Coordinate pPosition(analyzingX, analyzingY);
    auto piece = makePiece(analyzingChar, pPosition);
    boardInstance.updateSquare(std::make_pair(pPosition, piece));
    boardInstance.updateBlackPiecesVector(piece);
    analyzingX++;
    analyzingPosition++;
  }
}

/**
 * Function for creating the pointer to a specified piece.
 *
 * @param[in] pType The type of the piece: `PieceType::PAWN`, `PieceType::ROOK`,
 * `PieceType::KNIGHT`, `PieceType::BISHOP`, `PieceType::QUEEN`, `PieceType::KING`.
 * @param[in] pColor The color of the piece: `PieceColor::BLACK`, `PieceColor::WHITE`.
 * @param[in] pPosition The position of the piece.
 *
 * @return The pointer to the piece that has been created created.
 */
std::shared_ptr<Piece> GameManager::makePiece(const PieceType pType, const PieceColor pColor, const Coordinate &pPosition) const
{
  switch (pType)
  {
  case PieceType::PAWN:
    return std::make_shared<Pawn>(pColor, pPosition);
    break;
  case PieceType::ROOK:
    return std::make_shared<Rook>(pColor, pPosition);
    break;
  case PieceType::KNIGHT:
    return std::make_shared<Knight>(pColor, pPosition);
    break;
  case PieceType::BISHOP:
    return std::make_shared<Bishop>(pColor, pPosition);
    break;
  case PieceType::QUEEN:
    return std::make_shared<Queen>(pColor, pPosition);
    break;
  case PieceType::KING:
    return std::make_shared<King>(pColor, pPosition);
    break;

  default:
    return nullptr;
  }
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
  PieceColor pColor;
  if (std::isupper(pChar)) {
    pColor = PieceColor::WHITE;
  } else if (std::islower(pChar)) {
    pColor = PieceColor::BLACK;
    pChar = std::toupper(pChar);
  } else {
    throw std::invalid_argument("GameManager::makePiece(char, Coordinate) Invalid pieceString value."); 
  }

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
