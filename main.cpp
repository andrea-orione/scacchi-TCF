#include "GameManager.hh"

#include <iostream>
#include <memory>

int main(int argc, char *argv[])
{
  try
  {
    std::unique_ptr<GameManager> gm = std::make_unique<GameManager>();

    gm->StartGame();
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
