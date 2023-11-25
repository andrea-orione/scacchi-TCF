#include "include/Board.hh"

int main (int argc, char *argv[]) {
  Board provaBoard;
  provaBoard.printBoard();

  Board provaBoardSemplificata;
  provaBoardSemplificata.printBoard(true);

  return 0;
}
