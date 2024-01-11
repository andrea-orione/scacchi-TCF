#include "BoardFactory.hh"

#include <cctype>
#include <charconv>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "Bishop.hh"
#include "Board.hh"
#include "Coordinate.hh"
#include "King.hh"
#include "Knight.hh"
#include "Pawn.hh"
#include "Queen.hh"
#include "Rook.hh"
#include "VoidPiece.hh"

/**
 * Function for creating the pointer to a specified piece from.
 *
 * @param[in] pChar The `char` representing the piece.
 * @param[in] pPosition The position of the piece.
 * @param[in] hasMoved For king and rook, `false` by default.
 *
 * @return The pointer to the piece that has been created created.
 */
std::shared_ptr<Piece> BoardFactory::MakePiece(char pChar, const Coordinate pPosition, const bool hasRookMoved)
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
 * Function for initializing the board at the beginning of the game.
 */
void BoardFactory::InitializeStartingBoard() const
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
 * Function to initialize the board from a FEN string.
 *
 * It first analyzes the first part of the string containing the position of all
 * the pieces and updates the board
 *
 * @param[in] fenString The string containing the configuration to load.
 */
void BoardFactory::LoadFenPosition(std::string_view fenString) const
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
