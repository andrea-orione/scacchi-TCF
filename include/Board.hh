#pragma once

#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Coordinate.hh"
#include "Square.hh"
#include "Piece.hh"

using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::shared_ptr;
using std::string;
using std::vector;

/**
 * The most important class in the program.
 *
 * This class contains a map from the coordinates to the actual squares
 * that contain pieces.
 * It also has methods to accept moves from the command line, to move pieces
 * and check the game status.
 *
 * It is a singleton.
 */
class Board
{
public:
  static Board &Instance();

  Board(const Board &) = delete;
  Board(const Board &&) = delete;
  Board &operator=(const Board &) = delete;
  Board &operator=(const Board &&) = delete;

  /**
   * The default constructor.
   *
   * It initializes all 64 squares to an empty state.
   */
  void InitializeBoard();

  /**
   * Print the state of the board from the white perspective.
   *
   * It displays visually to the screen the board using UNICODE characters
   *
   * @param[in] simplified wether to use simplified chars to print
   *  (useful if terminal doesn't support special chars)
   */
  void printBoard(bool simplified = false) const;

  /**
   * Print the state of the board from the black perspective.
   *
   * It displays visually to the screen the board using UNICODE characters
   *
   * @param[in] simplified wether to use simplified chars to print
   *  (useful if terminal doesn't support special chars)
   */
  void printBoardReversed(bool simplified = false) const;

  /**
   * Function for updating the `squaresMap`.
   *
   * @param[in] piece Pair with the coordinate and the pointer to the piece to be added.
   */
  void AddPiece(pair<Coordinate, shared_ptr<Piece>> pair);

private:
  Board() {}

  map<Coordinate, shared_ptr<Piece>> squaresMap;
};
