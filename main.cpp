#include "Board.hh"
#include "Coordinate.hh"
#include "GameManager.hh"
#include <string>
#include <vector>
#include <iostream>

int main(int argc, char *argv[])
{
  GameManager *gm = new GameManager();

  gm->InitializeStartingBoard();
  gm->gameLoop();

  delete gm;

  std::cin.get();
}
