#pragma once

#include "Coordinate.hh"
#include <string>
#include <vector>

enum class PieceColor
{
  BLACK,
  WHITE,
  VOID
};

enum class PieceType
{
  PAWN,
  ROOK,
  KNIGHT,
  BISHOP,
  QUEEN,
  KING,
  VOID
};

/**
 * The abstract class for the chess Piece.
 */
class Piece
{
protected:
  PieceColor color;
  PieceType pieceType;
  std::string character;
  char literalCharacter;
  Coordinate position;

public:
  virtual ~Piece() {}

  /**
   * Return the string representing the Piece.
   *
   * @return The aforementioned string.
   */
  virtual std::string toString(bool literal = false) const = 0;

  /**
   * Return the vector with valid coordinates.
   *
   * It creates a vector containing all the coordinates that are reachable
   * by the piece from the square it's in.
   * It take in consideration the limits of the board and the other pieces.
   * Squares with friend pieces cannot be occupied while squares with opponent's
   * pieces can be occupied (capture) but not passed through.
   *
   * @return The aforementioned vector.
   */
  virtual bool isMoveValid(const Coordinate &endingPosition) const = 0;

  /**
   * Function for getting the color of the piece.
   *
   * @return The color of the piece.
   */
  PieceColor getColor() const { return color; }

  /**
   * Function for getting the type of the piece.
   *
   * @return The type of the piece.
   */
  PieceType getType() const { return pieceType; }

  /**
   * Function for getting the position of the piece.
   *
   * @return The position of the piece.
   */
  Coordinate getPosition() const { return position; }

  /**
   *
   * The position setter.
   *
   * @param[in] newPosition a coordinate object to assign to the position.
   */
  void setPosition(const Coordinate& newPosition) {position = newPosition;}
};
