#include "BoardFactory.hh"

#include <cctype>
#include <charconv>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string_view>

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
std::unique_ptr<Piece> BoardFactory::MakePiece(char pChar, const Coordinate pPosition, const bool hasRookMoved)
{
  // Check if void
  if (pChar == 0)
    return std::make_unique<VoidPiece>(pPosition);

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
    throw std::invalid_argument("BoardFactory::makePiece(char, Coordinate) Invalid value for char representing piece.");
  }

  // determine the type of the piece
  switch (pChar)
  {
  case 'P':
    return std::make_unique<Pawn>(pColor, pPosition);
  case 'R':
    return std::make_unique<Rook>(pColor, pPosition, hasRookMoved);
  case 'N':
    return std::make_unique<Knight>(pColor, pPosition);
  case 'B':
    return std::make_unique<Bishop>(pColor, pPosition);
  case 'Q':
    return std::make_unique<Queen>(pColor, pPosition);
  case 'K':
    return std::make_unique<King>(pColor, pPosition, false);
  default:
    throw std::invalid_argument("BoardFactory::makePiece(char, Coordinate) Invalid value for char representing piece.");
  }
}

/**
 * Function for initializing the board at the beginning of the game.
 */
void BoardFactory::InitializeStartingBoard() const
{
  try
  {
    // this->LoadFenPosition("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    this->LoadFenPosition("rnbqkbnr/pPpppppp/8/8/8/8/P1PPPPPP/RNBQKBNR w KQkq - 0 1");
    // this->LoadFenPosition("rnbqkbnr/ppp1pppp/8/8/3p4/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    // this->LoadFenPosition("1k6/7R/8/8/4K3/8/6Q1/8 w - - 0 1");
    // this->LoadFenPosition("k7/n7/8/8/8/8/7q/7K w - - 0 1");
    // this->LoadFenPosition("7k/7p/7P/8/8/1nK5/6Q1/8 w - - 0 1");
    // this->LoadFenPosition("rnb2k1r/pp1Pbppp/2p5/q7/2B5/8/PPPQNnPP/RNB1K2R w KQ - 3 9");
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
  Board &board = Board::Instance();
  board.ClearBoard();

  int analyzingPosition = fenString.find(" ");
  if (analyzingPosition == std::string_view::npos)
    throw std::invalid_argument("BoardFactory::loadFenPosition(string) Space not found.");
  this->LoadBoardPosition(fenString.substr(0, analyzingPosition));
  // ActivePiece
  analyzingPosition++;
  char analyzingChar = fenString.at(analyzingPosition);
  switch (analyzingChar)
  {
    case 'w':
      break;
    case 'b':
      board.IncrementMoveNumber();
      break;
    default:
      board.ClearBoard();
      throw std::invalid_argument("BoardFactory::loadFenPosition(string) Invalid active color");
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
        board.ClearBoard();
        throw std::invalid_argument("BoardFactory::loadFendPosition() Invalid castling section");
        break;
    }
    Piece* rook = board.GetPiece(rookPosition);
    if (rook->GetType() != PieceType::ROOK)
    {
      board.ClearBoard();
      throw std::invalid_argument("BoardFactory::loadFendPosition() Invalid castling section");
    }
    rook->Move(rookPosition);
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
  board.IncrementMoveNumber((iMoveNumber - 1) * 2);

  // enPassant
  if (hasEnPassant)
  {
    try
    {
      const Coordinate enPassantPawnPosition = Coordinate(enPassantSubstring);
      board.GetPiece(enPassantPawnPosition)->Move(enPassantPawnPosition);
    }
    catch (std::invalid_argument)
    {
      board.ClearBoard();
      throw std::invalid_argument("BoardFactory::loadFendPosition() Invalid en-passant section");
    }
  }
}

void BoardFactory::LoadBoardPosition(std::string_view boardString) const
{
  Board &board = Board::Instance();
  board.ClearBoard();

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
    analyzingChar = boardString.at(analyzingPosition);

    // Check if is a `/` or if it should be (if it shouldn't it will throw an error in the last part)
    if (analyzingX == 9 && analyzingChar != '/')
    {
      board.ClearBoard();
      throw std::invalid_argument("BoardFactory::loadFenPosition(string) Invalid string formatting.");
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
      std::unique_ptr<Piece> piece = MakePiece(analyzingChar, pPosition);
      if (piece->GetType() == PieceType::KING)
      {
        bool &hasKingColor = (piece->GetColor() == PieceColor::WHITE) ? hasWhiteKing : hasBlackKing;
        if (hasKingColor)
          throw std::invalid_argument("Too many kings");
        Coordinate &kingCoordinateColor = (piece->GetColor() == PieceColor::WHITE) ? whiteKingCoordinate : blackKingCoordinate;
        hasKingColor = true;
        kingCoordinateColor = pPosition;
      }
      board.InsertPiece(pPosition, std::move(piece));
    }
    catch (const std::invalid_argument &e)
    {
      board.ClearBoard();
      throw std::invalid_argument("BoardFactory::loadFenPosition(string) Invalid naming in FEN string.");
    }

    analyzingX++;
    analyzingPosition++;
  }
  if (!(hasBlackKing && hasWhiteKing))
  {
    board.ClearBoard();
    throw std::invalid_argument("BoardFactory::loadFenPosition(string) Not enough kings.");
  }
  board.AddKings(whiteKingCoordinate, blackKingCoordinate);
}
