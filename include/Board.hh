#pragma once

#include <map>
#include <string>
#include <vector>
#include <memory>

#include "Coordinate.hh"
#include "Piece.hh"

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

  Board(const Board &) = delete;             // delete copy constructor
  Board(const Board &&) = delete;            // delete move constructor
  Board &operator=(const Board &) = delete;  // delete assignment operator
  Board &operator=(const Board &&) = delete; // delete move assignment operator

  // void InitializeBoard();

  void printBoard(bool simplified = false) const;
  void printBoardReversed(bool simplified = false) const;

  void updateSquare(std::pair<Coordinate, std::shared_ptr<Piece>> &&square) noexcept;
  void updatePiecesVector(std::shared_ptr<Piece> &&newPiece) noexcept;
  
  bool isSquareAttacked(const Coordinate &square, const PieceColor attackerColor) const;
  void normalMove(std::shared_ptr<Piece> &movingPiece, const Coordinate &endingPosition);
  void castling(std::shared_ptr<Piece> &king, const Coordinate &kingEndingPosition);

  std::shared_ptr<Piece> getPiece(const Coordinate &position) const;

  void clearBoard();

  void printWhitePieces() const;
  void printBlackPieces() const;

private:
  Board();

  // Map defining the squares as {coordinate : pointer to piece}.
  std::map<Coordinate, std::shared_ptr<Piece>> squaresMap;

  // Vector with the pointers to the white pieces on the board.
  std::vector<std::shared_ptr<Piece>> whitePieces;
  // Vector with the pointers to the black pieces on the board.
  std::vector<std::shared_ptr<Piece>> blackPieces;

  // The pointer to the kings. Useful for fast checking if are in check.
  std::shared_ptr<Piece> whiteKing;
  std::shared_ptr<Piece> blackKing;
};


class InvalidMoveException : public std::exception 
{
public:
  std::string what();
};
