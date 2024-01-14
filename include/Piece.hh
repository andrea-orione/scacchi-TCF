#pragma once

#include <memory>

#include "Coordinate.hh"
#include "PieceMover.hh"
class PieceMover;


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
 * This struct contains the informations needed to make a move.
 * Theese are if the move is valid and the handler of the move.
 */
struct MoveInfo{
  bool valid;
  std::unique_ptr<PieceMover> moveHandler;
};

/**
 * The abstract class for the chess Piece.
 */
class Piece
{
protected:
  PieceColor color;
  PieceType pieceType;
  Coordinate position;
  char literal;

public:
  virtual ~Piece() {}

  /**
   * Function for determining whether a move is valid or not.
   *
   * It controls if the move indicated by the player is compatible
   * with the possible moves of the piece and if there are no other
   * pieces in the way.
   *
   * @param[in] endingPosition The square where the piece should move to.
   * @param[out] moveHandler The strategy that should handle the move.
   *
   * @return `true` if the move is valid, `false` if it's not.
   */
  virtual MoveInfo IsMoveValid(const Coordinate endingPosition) const = 0;

  char GetChar() const { return literal; }

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

  /**
   * Function for getting the number of the move when the pawn moved by two.
   *
   * Gets overridden only by the `Pawn` class, so it is also useful for
   * checking whether a piece is a pawn or not.
   *
   * @return 0 if the piece is not a pawn, the `doubleAdvancementMoveNumber` data
   * member if the piece is a pawn
   */
  virtual int GetDoubleAdvancementMoveNumber() const { return -1; }
};
