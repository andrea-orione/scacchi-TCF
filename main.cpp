#include "include/Board.hh"

int main (int argc, char *argv[]) {
  Board provaBoard;
  provaBoard.printBoardReversed();

  Board provaBoardSemplificata;
  provaBoardSemplificata.printBoardReversed(true);

  return 0;
}
