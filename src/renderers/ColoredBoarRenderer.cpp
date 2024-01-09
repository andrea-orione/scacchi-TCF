#include "ColoredBoardRenderer.hh"

#include <iostream>

#include "Board.hh"

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
      auto piece = board.GetPiece(Coordinate(column, row));
      auto &colorParameter = ((row + column) % 2) ? COLOR_WHITE : COLOR_BLACK;
      cout << colorParameter << " " << piece->ToString(false, true) << " ";
    }
    cout << COLOR_OFF;
    if (row == 8)
      cout << "   BLACK CAPTURED PIECES: " << board.GetCapturedPieces(PieceColor::BLACK);
    if (row == 6)
      cout << "   WHITE CAPTURED PIECES: " << board.GetCapturedPieces(PieceColor::WHITE);
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
      auto piece = board.GetPiece(Coordinate(column, row));
      auto &colorParameter = ((row + column) % 2) ? COLOR_WHITE : COLOR_BLACK;
      cout << colorParameter << " " << piece->ToString(false, true) << " ";
    }
    cout << COLOR_OFF;
    if (row == 1)
      cout << "   BLACK CAPTURED PIECES: " << board.GetCapturedPieces(PieceColor::BLACK);
    if (row == 3)
      cout << "   WHITE CAPTURED PIECES: " << board.GetCapturedPieces(PieceColor::WHITE);
    cout << '\n';
  }
  cout << "    h  g  f  e  d  c  b  a\n"
       << endl;
}
