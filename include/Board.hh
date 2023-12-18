#pragma once

#include <map>
#include <string>
#include <vector>
#include <memory>
#include <exception>

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

  void printWhiteBoard(bool simplified = false) const;
  void printBlackBoard(bool simplified = false) const;

  void updateSquare(std::pair<Coordinate, std::shared_ptr<Piece>> &&square) noexcept;
  void updatePiecesVector(std::shared_ptr<Piece> &&newPiece) noexcept;
  void addKings();

  bool isSquareAttacked(const Coordinate square, const PieceColor attackerColor) const;
  void normalMove(std::shared_ptr<Piece> &&movingPiece, const Coordinate endingPosition);

  std::shared_ptr<Piece> getPiece(const Coordinate position) const;

  void clearBoard();

  std::string getWhiteCapturedPieces() const;
  std::string getBlackCapturedPieces() const;

  void printWhitePieces() const;
  void printBlackPieces() const;

private:
  Board(); // private constructor
  void castling(std::shared_ptr<Piece> &&king, const Coordinate kingEndingPosition);

  // Map defining the squares as {coordinate : pointer to piece}.
  std::map<Coordinate, std::shared_ptr<Piece>> squaresMap;

  // Vector with the pointers to the white pieces on the board.
  std::vector<std::shared_ptr<Piece>> whitePieces;
  // Vector with the pointers to the black pieces on the board.
  std::vector<std::shared_ptr<Piece>> blackPieces;
  // Vector with the pointers to the white pieces captured.
  std::vector<std::shared_ptr<Piece>> whiteCapturedPieces;
  // Vector with the pointers to the black pieces captured.
  std::vector<std::shared_ptr<Piece>> blackCapturedPieces;

  // Pointer to the white king.
  std::shared_ptr<Piece> whiteKing;
  // Pointer to the black king.
  std::shared_ptr<Piece> blackKing;
};
