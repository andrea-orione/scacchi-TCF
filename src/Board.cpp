#include "Board.hh"

Board &Board::Instance()
{
  static Board instance;

  return instance;
}

void Board::InitializeBoard()
{
  squaresMap = map<Coordinate, Square>();

  for (int row = 1; row < 9; row++)
  {
    for (int column = 1; column < 9; column++)
    {
      pair<Coordinate, Square> squareCoordPair(Coordinate(column, row), Square());
      squaresMap.insert(squareCoordPair);
    }
  }
}

// TODO make this method const
void Board::printBoard(const bool &simplified) const
{
  string top = (simplified) ? "---------------------------------" : "╔═══╤═══╤═══╤═══╤═══╤═══╤═══╤═══╗";
  string middle = (simplified) ? "|---|---|---|---|---|---|---|---|" : "╟───┼───┼───┼───┼───┼───┼───┼───╢";
  string bottom = (simplified) ? "---------------------------------" : "╚═══╧═══╧═══╧═══╧═══╧═══╧═══╧═══╝";
  string border = (simplified) ? "|" : "║";
  string separator = (simplified) ? "|" : "│";

  cout << "\n   " << top << "\n";
  for (int row = 8; row > 0; row--)
  {
    cout << " " << row << " " << border << " ";
    for (int column = 1; column < 9; column++)
    {
      auto squareIterator = squaresMap.find(Coordinate(column, row));
      cout << squareIterator->second.toString(simplified);

      // Slightly inefficient but makes the code cleaner
      if (column != 8)
        cout << " " << separator << " ";
      else
        cout << " " << border;
    }
    if (row != 1)
      cout << "\n   " << middle << "\n";
    else
      cout << "\n   " << bottom << "\n";
  }
  cout << "     a   b   c   d   e   f   g   h\n\n";
}

// TODO make this method const
void Board::printBoardReversed(const bool &simplified) const
{
  string top = (simplified) ? "---------------------------------" : "╔═══╤═══╤═══╤═══╤═══╤═══╤═══╤═══╗";
  string middle = (simplified) ? "|---|---|---|---|---|---|---|---|" : "╟───┼───┼───┼───┼───┼───┼───┼───╢";
  string bottom = (simplified) ? "---------------------------------" : "╚═══╧═══╧═══╧═══╧═══╧═══╧═══╧═══╝";
  string border = (simplified) ? "|" : "║";
  string separator = (simplified) ? "|" : "│";

  cout << "\n   " << top << "\n";
  for (int row = 1; row < 9; row++)
  {
    cout << " " << row << " " << border << " ";
    for (int column = 8; column > 0; column--)
    {
      // Have to use iterator to make method const
      auto squareIterator = squaresMap.find(Coordinate(column, row));
      cout << squareIterator->second.toString(simplified);

      // Slightly inefficient but makes the code cleaner
      if (column != 1)
        cout << " " << separator << " ";
      else
        cout << " " << border;
    }
    if (row != 8)
      cout << "\n   " << middle << "\n";
    else
      cout << "\n   " << bottom << "\n";
  }
  cout << "     h   g   f   e   d   c   b   a\n\n";
}
