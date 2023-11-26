#include "include/Board.hh"
#include "include/Coordinate.hh"
#include "include/Movement.hh"

int main (int argc, char *argv[]) {
  // Board provaBoard;
  // provaBoard.printBoardReversed();

  // Board provaBoardSemplificata;
  // provaBoardSemplificata.printBoardReversed(true);

  Movement movimentoProva(-1,-1);
  Coordinate coordinataProva("e5");

  Movement movimentoProva2 = movimentoProva*4;
  Coordinate coordinataProva2 = coordinataProva+movimentoProva2;
  coordinataProva2.print();
  return 0;
}
