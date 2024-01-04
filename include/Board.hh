#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Coordinate.hh"
#include "Piece.hh"

//! @todo Delete testing functions (printWhitePieces() and printBlackPieces())
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

  void PrintWhiteBoard(bool simplified) const;
  void PrintBlackBoard(bool simplified) const;

  void UpdateSquare(std::pair<Coordinate, std::shared_ptr<Piece>> square);
  void UpdatePiecesVector();
  void AddKings(Coordinate whiteKingPosition, Coordinate blackKingPosition);

  bool IsKingInCheck(PieceColor kingColor) const;
  bool HasValidMoves(PieceColor playerColor);
  bool IsMaterialLacking() const;
  void NormalMove(std::shared_ptr<Piece> &&movingPiece, Coordinate endingPosition);
  void Promotion(std::shared_ptr<Piece> &&pawn, char promotionPiece, Coordinate endingPosition);

  std::shared_ptr<Piece> GetPiece(Coordinate position) const;

  void ClearBoard();
  void ResetMoveNumber() { moveNumber = 0; }
  void IncrementMoveNumber(int increment = 1) { moveNumber += increment; }
  int GetMoveNumber() const { return moveNumber; }

  std::string GetCapturedPieces(PieceColor pColor, bool literal = false) const;

  void printWhitePieces() const;
  void printBlackPieces() const;

private:
  Board(); // private constructor

  void Castling(std::shared_ptr<Piece> &&king, Coordinate kingEndingPosition);
  void EnPassant(std::shared_ptr<Piece> &&pawn, Coordinate pawnEndingPosition);

  bool IsSquareAttacked(Coordinate square, PieceColor attackerColor) const;

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
