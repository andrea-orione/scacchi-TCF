#include "Board.hh"
#include "Coordinate.hh"
#include "Movement.hh"
#include "Piece.hh"
#include "Factory.hh"

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

  Factory *f = new Factory();
  f->createWhitePieces();
  f->createBlackPieces();

  delete f;

  board.printBoard();

  return 0;
}
