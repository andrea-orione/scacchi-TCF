#pragma once

#include "Coordinate.hh"
#include <string>

/**
 * Enumeration representing the color of the piece.
 *
 * Can take three values: `BLACK`, `WHITE` and `VOID`.
 */
enum class PieceColor
{
  BLACK,
  WHITE,
  VOID
};

/**
 * Enumeration representing the type of the piece.
 *
 * Can take six values: `PAWN`, `ROOK`, `KNIGHT`, `BISHOP`, `QUEEN` and `KING`.
 */
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
  virtual std::string ToString(bool literal = false) const = 0;

  /**
   * Function for determining whether a move is valid or not.
   *
   * It controls if the move indicated by the player is compatible
   * with the possible moves of the piece and if there are no other
   * pieces in the way.
   *
   * @param[in] endingPosition The square where the piece should move to.
   *
   * @return `true` if the move is valid, `false` if it's not.
   */
  virtual bool IsMoveValid(const Coordinate endingPosition) const = 0;

  /**
   * Function for getting the color of the piece.
   *
   * @return The color of the piece.
   */
  PieceColor GetColor() const { return color; }

  /**
   * Function for getting the type of the piece.
   *
   * @return The type of the piece.
   */
  PieceType GetType() const { return pieceType; }

  /**
   * Function for getting the position of the piece.
   *
   * @return The position of the piece.
   */
  Coordinate GetPosition() const { return position; }

  /**
   * Function for moving the piece to anew square.
   *
   * @param[in] newPosition The square where to move the piece to.
   */
  virtual void Move(const Coordinate newPosition) { position = newPosition; }

  /**
   * Checks whether the piece can castle or not.
   *
   * For a default piece just returns false.
   * It will be overridden by rook and king.
   *
   * @return `true` if the piece can castle, `false` if it can't.
   */
  virtual bool CanCastle() const { return false; }

  virtual int GetDoubleAdvancementMoveNumber() const { return 0; }
};
