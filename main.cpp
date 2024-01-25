#include "GameManager.hh"

#include <iostream>

int main(int argc, char *argv[])
{
  try
  {
    GameManager game{};
    game.StartGame();
  }
  catch (const std::runtime_error &e)
  {
    std::cerr << e.what() << '\n';
  }
  catch (...)
  {
    printf("Some error occurred. \n");
  }

  return 0;
}
