#include "ColoredBoardRenderer.hh"

#include <iostream>
#include <map>
#include <string_view>

#include "Board.hh"
#include "Piece.hh"
#include "Utils.hh"

using std::cout;
using std::endl;

constexpr char COLOR_WHITE[] = "\u001b[38;5;0m\u001b[48;5;250m";
constexpr char COLOR_BLACK[] = "\u001b[38;5;0m\u001b[48;5;216m";
constexpr char COLOR_OFF[] = "\x1b[0m";

void ColoredBoardRenderer::PrintWhiteBoard() const
{
  const Board &board = Board::Instance();
  cout << "\n";
  for (int row = 8; row > 0; row--)
  {
    cout << " " << row << " ";
    for (int column = 1; column < 9; column++)
    {
      const auto &colorParameter = ((row + column) % 2) ? COLOR_WHITE : COLOR_BLACK;
      const Piece* piece = board.GetPiece(Coordinate(column, row));
      const auto &pieceChars = (piece->GetColor() == PieceColor::WHITE) ? utils::voidPiecesChars : utils::fullPiecesChars;
      cout << colorParameter << " " << pieceChars.at(piece->GetType()) << " ";
    }
    cout << COLOR_OFF;
    if (row == 8)
      cout << "   BLACK CAPTURED PIECES: " << this->PieceVectorToString(board.GetCapturedPieces(PieceColor::BLACK));
    if (row == 6)
      cout << "   WHITE CAPTURED PIECES: " << this->PieceVectorToString(board.GetCapturedPieces(PieceColor::WHITE));
    cout << '\n';
  }
  cout << "    a  b  c  d  e  f  g  h\n"
       << endl;
}

void ColoredBoardRenderer::PrintBlackBoard() const
{
  const Board &board = Board::Instance();
  cout << "\n";
  for (int row = 1; row < 9; row++)
  {
    cout << " " << row << " ";
    for (int column = 8; column > 0; column--)
    {
      const auto &colorParameter = ((row + column) % 2) ? COLOR_WHITE : COLOR_BLACK;
      const Piece* piece = board.GetPiece(Coordinate(column, row));
      const auto &pieceChars = (piece->GetColor() == PieceColor::WHITE) ? utils::voidPiecesChars : utils::fullPiecesChars;
      cout << colorParameter << " " << pieceChars.at(piece->GetType()) << " ";
    }
    cout << COLOR_OFF;
    if (row == 1)
      cout << "   BLACK CAPTURED PIECES: " << this->PieceVectorToString(board.GetCapturedPieces(PieceColor::BLACK));
    if (row == 3)
      cout << "   WHITE CAPTURED PIECES: " << this->PieceVectorToString(board.GetCapturedPieces(PieceColor::WHITE));
    cout << '\n';
  }
  cout << "    h  g  f  e  d  c  b  a\n"
       << endl;
}

std::string ColoredBoardRenderer::PieceVectorToString(const std::vector<Piece*>& pieceVector) const
{
  std::string vectorString{};
  for (const auto piece : pieceVector)
  {
    const auto &pieceChars = (piece->GetColor() == PieceColor::WHITE) ? utils::fullPiecesChars : utils::voidPiecesChars;
    vectorString += (std::string(pieceChars.at(piece->GetType())) + " ");
  }
  return vectorString;
}
