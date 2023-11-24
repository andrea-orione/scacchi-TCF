#include "include/Board.hh"
#include "include/Coordinates.hh"
#include <iostream>
#include <stdexcept>
#include <string>

void try_out_of_range(int a, int b)
{
  try {
    Coordinates coordinates2(a,b);
    coordinates2.print();
  
  } catch (std::out_of_range) {
    std::cout << "Funziona con " << a << " e " << b << std::endl;
  }
}

int main (int argc, char *argv[])
{
  // Board provaBoard;
  // provaBoard.printBoard();

  Coordinates coordinates2('a',2);
  
  coordinates2.print();

  Coordinates coordinates3(std::string("c"), 3);
  coordinates3.print();

  // Coordinates coordinates3("a3");
  // coordinates3.print();



  return 0;
}
