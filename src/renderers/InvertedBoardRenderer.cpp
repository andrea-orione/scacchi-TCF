#include "InvertedBoardRenderer.hh"

#include <iostream>
#include <map>
#include <string_view>

#include "Board.hh"
#include "Piece.hh"
#include "Utils.hh"

using std::cout;
using std::endl;

constexpr std::string_view top = "╔═══╤═══╤═══╤═══╤═══╤═══╤═══╤═══╗";
constexpr std::string_view middle = "╟───┼───┼───┼───┼───┼───┼───┼───╢";
constexpr std::string_view bottom = "╚═══╧═══╧═══╧═══╧═══╧═══╧═══╧═══╝";
constexpr std::string_view border = "║";
constexpr std::string_view separator = "│";

void InvertedBoardRenderer::PrintWhiteBoard() const
{
  const Board &board = Board::Instance();
  cout << "\n   " << top << "\n";
  for (int row = 8; row > 0; row--)
  {
    cout << " " << row << " " << border << " ";
    for (int column = 1; column < 9; column++)
    {
      const Piece* piece = board.GetPiece(Coordinate(column, row)).get();
      const auto &pieceChars = (piece->GetColor() == PieceColor::WHITE) ? utils::voidPiecesChars : utils::fullPiecesChars;
      cout << pieceChars.at(piece->GetType());

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

void InvertedBoardRenderer::PrintBlackBoard() const
{
  const Board &board = Board::Instance();
  cout << "\n   " << top << "\n";
  for (int row = 1; row < 9; row++)
  {
    cout << " " << row << " " << border << " ";
    for (int column = 8; column > 0; column--)
    {
      const Piece* piece = board.GetPiece(Coordinate(column, row)).get();
      const auto &pieceChars = (piece->GetColor() == PieceColor::WHITE) ? utils::voidPiecesChars : utils::fullPiecesChars;
      cout << pieceChars.at(piece->GetType());

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

std::string InvertedBoardRenderer::PieceVectorToString(const std::vector<Piece*>& pieceVector) const
{
  std::string vectorString{};
  for (const auto piece : pieceVector)
  {
    const auto &pieceChars = (piece->GetColor() == PieceColor::WHITE) ? utils::voidPiecesChars : utils::fullPiecesChars;
    vectorString += (std::string(pieceChars.at(piece->GetType())) + " ");
  }
  return vectorString;
}
