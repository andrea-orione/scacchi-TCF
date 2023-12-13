#include "Board.hh"
#include "Coordinate.hh"
#include "Utils.hh"
#include "Piece.hh"

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using std::cout;
using std::endl;

/**
 * The default constructor.
 *
 * It initializes all 64 squares to an empty state.
 */
Board::Board()
{
  squaresMap = std::map<Coordinate, std::shared_ptr<Piece>>();
  whitePieces = std::vector<std::shared_ptr<Piece>>();
  blackPieces = std::vector<std::shared_ptr<Piece>>();
  whiteKing = nullptr;
  blackKing = nullptr;

  for (int row = 1; row < 9; row++)
  {
    for (int column = 1; column < 9; column++)
    {
      squaresMap.insert(std::make_pair(Coordinate(column, row), nullptr));
    }
  }
}

/**
 * Static method for accessing the singleton instance.
 *
 * @return The reference to the instance of the board (singleton).
 */
Board &Board::Instance()
{
  static Board instance;

  return instance;
}

/**
 * Print the state of the board from the white perspective.
 *
 * It displays visually to the screen the board using UNICODE characters
 *
 * @param[in] simplified wether to use simplified chars to print
 *  (useful if terminal doesn't support special chars)
 */
void Board::printBoard(bool simplified) const
{
  std::string top = (simplified) ? "---------------------------------" : "╔═══╤═══╤═══╤═══╤═══╤═══╤═══╤═══╗";
  std::string middle = (simplified) ? "|---|---|---|---|---|---|---|---|" : "╟───┼───┼───┼───┼───┼───┼───┼───╢";
  std::string bottom = (simplified) ? "---------------------------------" : "╚═══╧═══╧═══╧═══╧═══╧═══╧═══╧═══╝";
  std::string border = (simplified) ? "|" : "║";
  std::string separator = (simplified) ? "|" : "│";

  cout << "\n   " << top << "\n";
  for (int row = 8; row > 0; row--)
  {
    cout << " " << row << " " << border << " ";
    for (int column = 1; column < 9; column++)
    {
      auto piecePtr = squaresMap.find(Coordinate(column, row))->second;

      if (piecePtr == nullptr)
        cout << " ";
      else
        cout << piecePtr->toString(simplified);

      // Slightly inefficient but makes the code cleaner
      if (column != 8)
        cout << " " << separator << " ";
      else
        cout << " " << border;
    }
    if (row != 1)
      cout << "\n   " << middle << "\n";
    else
      cout << "\n   " << bottom << "\n";
  }
  cout << "     a   b   c   d   e   f   g   h\n"
       << endl;
}

/**
 * Print the state of the board from the black perspective.
 *
 * It displays visually to the screen the board using UNICODE characters
 *
 * @param[in] simplified wether to use simplified chars to print
 *  (useful if terminal doesn't support special chars)
 */
void Board::printBoardReversed(bool simplified) const
{
  std::string top = (simplified) ? "---------------------------------" : "╔═══╤═══╤═══╤═══╤═══╤═══╤═══╤═══╗";
  std::string middle = (simplified) ? "|---|---|---|---|---|---|---|---|" : "╟───┼───┼───┼───┼───┼───┼───┼───╢";
  std::string bottom = (simplified) ? "---------------------------------" : "╚═══╧═══╧═══╧═══╧═══╧═══╧═══╧═══╝";
  std::string border = (simplified) ? "|" : "║";
  std::string separator = (simplified) ? "|" : "│";

  cout << "\n   " << top << "\n";
  for (int row = 1; row < 9; row++)
  {
    cout << " " << row << " " << border << " ";
    for (int column = 8; column > 0; column--)
    {
      auto piecePtr = squaresMap.find(Coordinate(column, row))->second;

      if (piecePtr == nullptr)
        cout << " ";
      else
        cout << piecePtr->toString(simplified);

      // Slightly inefficient but makes the code cleaner
      if (column != 1)
        cout << " " << separator << " ";
      else
        cout << " " << border;
    }
    if (row != 8)
      cout << "\n   " << middle << "\n";
    else
      cout << "\n   " << bottom << "\n";
  }
  cout << "     h   g   f   e   d   c   b   a\n"
       << endl;
}

/**
 * Function for updating the `squaresMap`.
 *
 * @param[in] square The `std::pair` representing the square (see `squaresMap`).
 */
void Board::updateSquare(std::pair<Coordinate, std::shared_ptr<Piece>> &&square) noexcept
{
  squaresMap[square.first] = square.second;
}

/**
 * Function for adding pieces to the `whitePieces` and `blackPieces` vectors.
 *
 * @param[in] newPiece The pointer to the piece to be added.
 */
void Board::updatePiecesVector(std::shared_ptr<Piece> &&newPiece) noexcept
{
  if (newPiece->getColor() == PieceColor::BLACK)
    blackPieces.push_back(newPiece);
  else if (newPiece->getColor() == PieceColor::WHITE)
    whitePieces.push_back(newPiece);
}

bool Board::isSquareAttacked(const Coordinate &square, const PieceColor attackerColor) const
{
  const std::vector<std::shared_ptr<Piece>> &attackerVector = (attackerColor == PieceColor::WHITE) ? whitePieces : blackPieces;
  for (auto attackingPiece : attackerVector) {
    if (attackingPiece->isMoveValid(square)) return true;
  }
  return false;
}

void Board::normalMove(std::shared_ptr<Piece> &movingPiece, const Coordinate &endingPosition)
{
  if (!(movingPiece->isMoveValid(endingPosition))) throw InvalidMoveException();

  const Coordinate startingPosition = movingPiece->getPosition();
  std::vector<std::shared_ptr<Piece>> &opponentPieceVector = (movingPiece->getColor() == PieceColor::WHITE) ? whitePieces : blackPieces;
  std::shared_ptr<Piece> temporaryStorageCapturedPiece = squaresMap[endingPosition];
  squaresMap[endingPosition] = movingPiece;
  squaresMap[startingPosition] = nullptr; // TODO Change
  
  std::shared_ptr<Piece> &friendKing = (movingPiece->getColor() == PieceColor::WHITE) ? whiteKing : blackKing; 
  opponentPieceVector.erase(std::find(opponentPieceVector.begin(), opponentPieceVector.end(), temporaryStorageCapturedPiece));
  // Valid move case
  if (!(isSquareAttacked(friendKing->getPosition(), !(movingPiece->getColor())))) {
    movingPiece->setPosition(endingPosition);
    return;
  }
  
  // Invalid move case. Resetting the board. // TODO change
  if(temporaryStorageCapturedPiece != nullptr) opponentPieceVector.push_back(temporaryStorageCapturedPiece);
  squaresMap[startingPosition] = movingPiece;
  squaresMap[endingPosition] = temporaryStorageCapturedPiece;
  throw InvalidMoveException();
}

void Board::castling(std::shared_ptr<Piece> &king, const Coordinate &kingEndingPosition)
{
  if (!(king->isMoveValid(kingEndingPosition))) throw InvalidMoveException();

  //Preliminary control that the king isn't in check
  const Coordinate kingStartingPosition = king->getPosition();
  if (isSquareAttacked(kingStartingPosition, king->getColor())) throw InvalidMoveException();

  const int rookY = kingStartingPosition.getY();
  const Coordinate rookStartingPosition = (kingEndingPosition.getX() == 7) ? Coordinate(8, rookY) : Coordinate(1, rookY);
  const Coordinate rookEndingPosition = (kingEndingPosition.getX() == 7) ? Coordinate(6, rookY) : Coordinate(4, rookY);
  squaresMap[kingEndingPosition] = squaresMap[kingStartingPosition];
  squaresMap[rookEndingPosition] = squaresMap[rookStartingPosition];
  squaresMap[kingStartingPosition] = nullptr;
  squaresMap[rookStartingPosition] = nullptr;

  if (!(isSquareAttacked(kingEndingPosition, king->getColor()) && isSquareAttacked(rookEndingPosition, king->getColor())))
  {
    squaresMap[kingEndingPosition]->setPosition(kingEndingPosition);
    squaresMap[rookEndingPosition]->setPosition(rookEndingPosition);
    return;
  }
  
  squaresMap[kingStartingPosition] = squaresMap[kingEndingPosition];
  squaresMap[rookStartingPosition] = squaresMap[rookEndingPosition];
  squaresMap[kingEndingPosition] = nullptr;
  squaresMap[rookEndingPosition] = nullptr;
  throw  InvalidMoveException();
}

std::shared_ptr<Piece> Board::getPiece(const Coordinate &position) const
{
  return squaresMap.find(position)->second;
}

/**
 * Function for clearing the board.
 */
void Board::clearBoard()
{
  whitePieces.clear();
  blackPieces.clear();
  whiteKing = nullptr;
  blackKing = nullptr;
  for (int row = 1; row < 9; row++)
  {
    for (int column = 1; column < 9; column++)
    {
      squaresMap[Coordinate(column, row)] = nullptr;
    }
  }
}

/**
 * JUST FOR TESTING
 */
void Board::printWhitePieces() const
{
  cout << "WHITE PIECES\n";
  cout << "------------\n";
  for (auto piece : whitePieces)
  {
    cout << piece->toString() << " ";
  }
  cout << "\n";
}

/**
 * JUST FOR TESTING
 */
void Board::printBlackPieces() const
{
  cout << "BLACK PIECES\n";
  cout << "------------\n";
  for (auto piece : blackPieces)
  {
    cout << piece->toString() << " ";
  }
  cout << "\n";
}


std::string InvalidMoveException::what() {
    return "This move is invalid";
}
