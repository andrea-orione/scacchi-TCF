#include "Board.hh"
#include "Coordinate.hh"
#include "GameManager.hh"
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
  try
  {
    GameManager *gm = new GameManager();

    gm->startGame();
    gm->gameLoop();

    delete gm;
  }
  catch (const std::runtime_error &e)
  {
    std::cerr << e.what() << '\n';
  }
  catch (...)
  {
    printf("Some error occurred. \n");
  }

  std::cin.get();
}
