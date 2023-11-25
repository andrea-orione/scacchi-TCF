#pragma once

#include "Coordinate.hh"
#include "Square.hh"
#include <map>
#include <vector>

/**
 * The most important class in the program.
 * 
 * This class contains a map from the coordinates to the actual squares 
 * that contain pieces.
 * It also has methods to accept moves from the command line, to move pieces
 * and check the game status.
 */
class Board
{
public:
  /**
    * The default constructor.
    *
    * It initializes all 64 squares to an empty state.
    */
  Board();
  
  //TODO make this method constant (there are some problems with the iterator)
  /**
    * Print the state of the board.
    *
    * It displays visually to the screen the board using UNICODE characters
    * 
    * @param[in] simplified wether to use simplified chars to print
    *  (useful if terminal doesn't support special chars)
    */
  void printBoard(bool simplified=false);

private:
  std::map<Coordinate, Square> squaresMap;
};
