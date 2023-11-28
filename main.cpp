#include "Board.hh"
#include "Coordinate.hh"
#include "Movement.hh"
#include "Piece.hh"
#include "Bishop.hh"

int main(int argc, char *argv[])
{
  // Board provaBoard;
  // provaBoard.printBoardReversed();

  // Board provaBoardSemplificata;
  // provaBoardSemplificata.printBoardReversed(true);

  // Movement movimentoProva(-1, -1);
  // Coordinate coordinataProva("e5");

  // Movement movimentoProva2 = movimentoProva * 4;
  // Coordinate coordinataProva2 = coordinataProva + movimentoProva2;
  // coordinataProva2.print();

  Board &board = Board::Instance();
  board.printBoard();

  Bishop *p = new Bishop(PieceType::WHITE);
  cout << p->toString() << endl;

  return 0;
}
