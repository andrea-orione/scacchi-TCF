#include "SimplifiedBoardRenderer.hh"

#include <iostream>
#include <map>
#include <string_view>

#include "Board.hh"
#include "Piece.hh"

using std::cout;
using std::endl;

constexpr std::string_view top = "---------------------------------";
constexpr std::string_view middle = "|---|---|---|---|---|---|---|---|";
constexpr std::string_view bottom = "---------------------------------";
constexpr std::string_view border = "|";
constexpr std::string_view separator = "|";

const std::map<PieceType, std::string_view> whitePiecesChars = {
  {PieceType::PAWN, "P"},
  {PieceType::ROOK, "R"},
  {PieceType::KNIGHT, "N"},
  {PieceType::BISHOP, "B"},
  {PieceType::QUEEN, "Q"},
  {PieceType::KING, "K"},
  {PieceType::VOID, " "}};

const std::map<PieceType, std::string_view> blackPiecesChars = {
  {PieceType::PAWN, "p"},
  {PieceType::ROOK, "r"},
  {PieceType::KNIGHT, "n"},
  {PieceType::BISHOP, "b"},
  {PieceType::QUEEN, "q"},
  {PieceType::KING, "k"},
  {PieceType::VOID, " "}};

void SimplifiedBoardRenderer::PrintWhiteBoard() const
{
  const Board &board = Board::Instance();
  cout << "\n   " << top << "\n";
  for (int row = 8; row > 0; row--)
  {
    cout << " " << row << " " << border << " ";
    for (int column = 1; column < 9; column++)
    {
      cout << this->PieceToString(board.GetPiece(Coordinate(column, row)));

      // Slightly inefficient but makes the code cleaner
      if (column != 8)
        cout << " " << separator << " ";
      else
        cout << " " << border;
    }
    if (row == 8)
      cout << "   BLACK CAPTURED PIECES: " << this->PieceVectorToString(board.GetCapturedPieces(PieceColor::BLACK));
    if (row == 7)
      cout << "   WHITE CAPTURED PIECES: " << this->PieceVectorToString(board.GetCapturedPieces(PieceColor::WHITE));
    if (row != 1)
      cout << "\n   " << middle << "\n";
    else
      cout << "\n   " << bottom << "\n";
  }
  cout << "     a   b   c   d   e   f   g   h\n"
       << endl;
}

void SimplifiedBoardRenderer::PrintBlackBoard() const
{
  const Board &board = Board::Instance();
  cout << "\n   " << top << "\n";
  for (int row = 1; row < 9; row++)
  {
    cout << " " << row << " " << border << " ";
    for (int column = 8; column > 0; column--)
    {
      cout << this->PieceToString(board.GetPiece(Coordinate(column, row)));

      // Slightly inefficient but makes the code cleaner
      if (column != 1)
        cout << " " << separator << " ";
      else
        cout << " " << border;
    }
    if (row == 1)
      cout << "   BLACK CAPTURED PIECES: " << this->PieceVectorToString(board.GetCapturedPieces(PieceColor::BLACK));
    if (row == 2)
      cout << "   WHITE CAPTURED PIECES: " << this->PieceVectorToString(board.GetCapturedPieces(PieceColor::WHITE));
    if (row != 8)
      cout << "\n   " << middle << "\n";
    else
      cout << "\n   " << bottom << "\n";
  }
  cout << "     h   g   f   e   d   c   b   a\n"
       << endl;
}
