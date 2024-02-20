#pragma once

#include <map>
#include <memory>
#include <vector>

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

  void AddKings(Coordinate whiteKingPosition, Coordinate blackKingPosition);
  std::unique_ptr<Piece> ReplacePiece(Coordinate position, std::unique_ptr<Piece> piece);
  std::unique_ptr<Piece> RemovePiece(Coordinate position);
  void InsertPiece(Coordinate position, std::unique_ptr<Piece> piece);

  bool IsSquareAttacked(Coordinate square, PieceColor attackerColor) const;

  bool IsKingInCheck(PieceColor kingColor) const;
  bool HasValidMoves(PieceColor playerColor);
  bool IsMaterialLacking() const;

  Piece* GetPiece(Coordinate position) const { return squaresMap.at(position).get(); }

  void ClearBoard();
  void ResetMoveNumber() { moveNumber = 0; }
  void IncrementMoveNumber(int increment = 1) { moveNumber += increment; }
  int GetMoveNumber() const { return moveNumber; }

  std::vector<Piece*> GetCapturedPieces(PieceColor pColor) const;
  void AddCapturedPiece(const std::unique_ptr<Piece> piece);

  std::string GetFenPosition() const;

private:
  Board(); // private constructor

  std::map<Coordinate, std::unique_ptr<Piece>> squaresMap;  // Map defining the squares as {coordinate : pointer to piece}.

  std::vector<Piece*> whitePieces;  // Vector with the pointers to the white pieces on the board.
  std::vector<Piece*> blackPieces;  // Vector with the pointers to the black pieces on the board.
  std::vector<std::unique_ptr<Piece>> whiteCapturedPieces;  // Vector with the pointers to the white pieces captured.
  std::vector<std::unique_ptr<Piece>> blackCapturedPieces;  // Vector with the pointers to the black pieces captured.
  Piece* whiteKing;  // Pointer to the white king.
  Piece* blackKing; // Pointer to the black king.

  int moveNumber;  // The number of moves done.
};
