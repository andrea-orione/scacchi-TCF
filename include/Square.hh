#pragma once

#include "Piece.hh"

//TODO Try deleting this class and replacing with a EmptyPiece that inherits from Piece. Then replace Square with Piece in Board.
//TODO Delete DEPRECATED methods.
/**
 * The Square Class.
 *
 * It represents a generic square on the board.
 * It may contain a piece inside (pointed by the piece attribute),
 * in this case the occupied attribute is true, otherwise false.
 */
class Square
{
public:
  /**
   * The default constructor.
   *
   * It initializes the square as void.
   */
  Square();
  
  /**
   * DEPRECATED CONSTRUCTOR, ONLY FOR TESTING.
   * 
   * Initializes the square with a piece inside.
   * Use the default constructor and the setPiece method instead.
   */
  Square(Piece *occupyingPiece);

  /**
   * The occupied getter.
   * 
   * @return the occupied value.
   */
  bool getOccupied() const;

  /**
   * DEPRECATED occupied SETTER, ONLY FOR TESTING.
   * 
   * @param[in] newOccupied the new occupied value.
   */
  void setOccupied(bool &newOccupied);

  /**
   * The piece getter.
   *
   * @return the piece pointer contained in the square.
   */
  Piece *getPiece() const;

  /**
   * The piece setter.
   *
   * @param[in] newPiece the new Piece pointer to be contained in the square.
   */
  void setPiece(Piece *&);

  /**
   * DEPRECATED, ONLY FOR TESTING. Print the content of the square to the screen.
   *
   * Use toString instead.
   *
   * @param[in] simplified wether to use simplified chars to print
   *  (useful if terminal doesn't support special chars)
   */
  void printSquareContent(bool simplified=false) const;

  /**
   * Return the string representing the content of the square.
   *
   * @param[in] simplified wether to use simplified chars to print
   *  (useful if terminal doesn't support special chars)
   * @return the above described string.
   */
  std::string toString(bool simplified=false) const;

private:
  bool occupied;
  Piece *piece;
};
