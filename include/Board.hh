#pragma once

#include <map>
#include <string>
#include <vector>
#include <memory>
#include <exception>

#include "Coordinate.hh"
#include "Piece.hh"

//TODO Delete testing functions (printWhitePieces() and printBlackPieces())
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

  void printWhiteBoard(bool simplified) const;
  void printBlackBoard(bool simplified) const;

  void updateSquare(std::pair<Coordinate, std::shared_ptr<Piece>> &&square) noexcept;
  void updatePiecesVector();
  void addKings(const Coordinate whiteKingPosition, const Coordinate blackKingPosition);

  bool isSquareAttacked(const Coordinate square, const PieceColor attackerColor) const;
  void normalMove(std::shared_ptr<Piece> &&movingPiece, const Coordinate endingPosition);

  std::shared_ptr<Piece> getPiece(const Coordinate position) const;

  void clearBoard();
  void resetMoveNumber() { moveNumber = 0; }
  void incrementMoveNumber(const int increment = 1) { moveNumber += increment; }
  int getMoveNumber() const { return moveNumber; }

  std::string getWhiteCapturedPieces(const bool literal = false) const;
  std::string getBlackCapturedPieces(const bool literal = false) const;

  void printWhitePieces() const;
  void printBlackPieces() const;

private:
  Board(); // private constructor

  void castling(std::shared_ptr<Piece> &&king, const Coordinate kingEndingPosition);
  void enPassant(std::shared_ptr<Piece> &&pawn, const Coordinate pawnEndingPosition);

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

  // The number of moves done.
  int moveNumber;

  // Pointer to the white king.
  std::shared_ptr<Piece> whiteKing;
  // Pointer to the black king.
  std::shared_ptr<Piece> blackKing;
};
