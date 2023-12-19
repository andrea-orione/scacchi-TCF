#include "Board.hh"
#include "Coordinate.hh"
#include "GameManager.hh"
#include "Movement.hh"
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
 * It creates the 64 squares.
 */
Board::Board()
{
  squaresMap = std::map<Coordinate, std::shared_ptr<Piece>>();
  whitePieces = std::vector<std::shared_ptr<Piece>>();
  blackPieces = std::vector<std::shared_ptr<Piece>>();
  whiteCapturedPieces = std::vector<std::shared_ptr<Piece>>();
  blackCapturedPieces = std::vector<std::shared_ptr<Piece>>();
  whiteKing = nullptr;
  blackKing = nullptr;

  for (int row = 1; row < 9; row++)
  {
    for (int column = 1; column < 9; column++)
    {
      Coordinate position(column, row);
      squaresMap.insert(std::make_pair(position, GameManager::makePiece(0, position)));
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
 * Print the state of the board and the captured pieces from the white perspective.
 *
 * It displays visually to the screen the board using UNICODE characters
 *
 * @param[in] simplified wether to use simplified chars to print
 *  (useful if terminal doesn't support special chars)
 */
void Board::printWhiteBoard(bool simplified) const
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
      cout << piecePtr->toString(simplified);

      // Slightly inefficient but makes the code cleaner
      if (column != 8)
        cout << " " << separator << " ";
      else
        cout << " " << border;
    }
    if (row == 8)
      cout << "   BLACK CAPTURED PIECES: " << getBlackCapturedPieces(simplified);
    if (row == 7)
      cout << "   WHITE CAPTURED PIECES: " << getWhiteCapturedPieces(simplified);
    if (row != 1)
      cout << "\n   " << middle << "\n";
    else
      cout << "\n   " << bottom << "\n";
  }
  cout << "     a   b   c   d   e   f   g   h\n"
       << endl;
}

/**
 * Print the state of the board and the captured pieces from the black perspective.
 *
 * It displays visually to the screen the board using UNICODE characters
 *
 * @param[in] simplified wether to use simplified chars to print
 *  (useful if terminal doesn't support special chars)
 */
void Board::printBlackBoard(bool simplified) const
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
      cout << piecePtr->toString(simplified);

      // Slightly inefficient but makes the code cleaner
      if (column != 1)
        cout << " " << separator << " ";
      else
        cout << " " << border;
    }
    if (row == 1)
      cout << "   BLACK CAPTURED PIECES: " << getBlackCapturedPieces(simplified);
    if (row == 2)
      cout << "   WHITE CAPTURED PIECES: " << getWhiteCapturedPieces(simplified);
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
void Board::updatePiecesVector()
{
  for (auto iterator = squaresMap.begin(); iterator != squaresMap.end(); iterator++) 
  {
    if (iterator->second->getColor() == PieceColor::BLACK)
      blackPieces.push_back(iterator->second);
    else if (iterator->second->getColor() == PieceColor::WHITE)
      whitePieces.push_back(iterator->second);
  }
}

/**
 * Function for updating the data members `whiteKing` and `blackKing`.
 */
void Board::addKings(const Coordinate whiteKingPosition, const Coordinate blackKingPosition)
{
  whiteKing = getPiece(whiteKingPosition);
  blackKing = getPiece(blackKingPosition);
}

/**
 *
 */
bool Board::isSquareAttacked(const Coordinate square, const PieceColor attackerColor) const
{
  const std::vector<std::shared_ptr<Piece>> &attackerVector = (attackerColor == PieceColor::WHITE) ? whitePieces : blackPieces;
  for (auto attackingPiece : attackerVector)
  {
    if (attackingPiece->isMoveValid(square))
      return true;
  }
  return false;
}

/**
 *
 */
void Board::normalMove(std::shared_ptr<Piece> &&movingPiece, const Coordinate endingPosition)
{
  try
  {
    if (!(movingPiece->isMoveValid(endingPosition)))
      throw InvalidMoveException("This move is not allowed. This piece cannot reach that position.");
  } catch (const CastlingSignal)
  {
    castling(std::move(movingPiece), endingPosition);
    return;
  } catch (const EnPassantSignal)
  {
    enPassant(std::move(movingPiece), endingPosition);
  }

  const Coordinate startingPosition = movingPiece->getPosition();
  std::vector<std::shared_ptr<Piece>> &opponentPieceVector = (movingPiece->getColor() == PieceColor::WHITE) ? blackPieces : whitePieces;
  std::vector<std::shared_ptr<Piece>> &opponentCapturedPieceVector = (movingPiece->getColor() == PieceColor::WHITE) ? blackCapturedPieces : whiteCapturedPieces;
  std::shared_ptr<Piece> temporaryStorageCapturedPiece = squaresMap[endingPosition];
  squaresMap[endingPosition] = movingPiece;
  squaresMap[startingPosition] = GameManager::makePiece(0, startingPosition);
  std::shared_ptr<Piece> &friendKing = (movingPiece->getColor() == PieceColor::WHITE) ? whiteKing : blackKing;
  if (temporaryStorageCapturedPiece->getColor() != PieceColor::VOID)
    opponentPieceVector.erase(std::find(opponentPieceVector.begin(), opponentPieceVector.end(), temporaryStorageCapturedPiece));

  // Valid move case
  if (!isSquareAttacked(friendKing->getPosition(), !(movingPiece->getColor())))
  {
    movingPiece->move(endingPosition);
    if (temporaryStorageCapturedPiece->getType() != PieceType::VOID)
      opponentCapturedPieceVector.push_back(temporaryStorageCapturedPiece);
    this->incrementMoveNumber();
    return;
  }

  // Invalid move case. Resetting the board.
  if (temporaryStorageCapturedPiece->getColor() != PieceColor::VOID)
    opponentPieceVector.push_back(temporaryStorageCapturedPiece);
  squaresMap[startingPosition] = movingPiece;
  squaresMap[endingPosition] = temporaryStorageCapturedPiece;
  throw InvalidMoveException("This move is not allowed. The king would be in check.");
}

/**
 *
 */
void Board::castling(std::shared_ptr<Piece> &&king, const Coordinate kingEndingPosition)
{
  // Preliminary control that the king isn't in check
  const Coordinate kingStartingPosition = king->getPosition();
  if (isSquareAttacked(kingStartingPosition, king->getColor()))
    throw InvalidMoveException("Castling is not allowed. The king is in check.");

  const int rookY = kingStartingPosition.getY();
  const Coordinate rookStartingPosition = (kingEndingPosition.getX() == 7) ? Coordinate(8, rookY) : Coordinate(1, rookY);
  const Coordinate rookEndingPosition = (kingEndingPosition.getX() == 7) ? Coordinate(6, rookY) : Coordinate(4, rookY);
  squaresMap[kingEndingPosition] = squaresMap[kingStartingPosition];
  squaresMap[rookEndingPosition] = squaresMap[rookStartingPosition];
  squaresMap[kingStartingPosition] = GameManager::makePiece(0, kingStartingPosition);
  squaresMap[rookStartingPosition] = GameManager::makePiece(0, rookStartingPosition);

  if (!(isSquareAttacked(kingEndingPosition, king->getColor()) && isSquareAttacked(rookEndingPosition, king->getColor())))
  {
    squaresMap[kingEndingPosition]->move(kingEndingPosition);
    squaresMap[rookEndingPosition]->move(rookEndingPosition);
    this->incrementMoveNumber();
    return;
  }

  squaresMap[kingStartingPosition] = squaresMap[kingEndingPosition];
  squaresMap[rookStartingPosition] = squaresMap[rookEndingPosition];
  squaresMap[kingEndingPosition] = GameManager::makePiece(0, kingEndingPosition);
  squaresMap[rookEndingPosition] = GameManager::makePiece(0, rookEndingPosition);
  throw InvalidMoveException("Castling is not allowed. The king cannot pass through or end in check.");
}

void Board::enPassant(std::shared_ptr<Piece> &&pawn, const Coordinate pawnEndingPosition)
{
  const Coordinate pawnStartingPosition = pawn->getPosition();
  const Movement capturingMovement = (pawn->getColor() == PieceColor::WHITE) ? Movement(0, -1) : Movement(0, 1);
  const Coordinate capturedPawnPosition = pawnEndingPosition + capturingMovement;

  std::shared_ptr<Piece> capturedPawn = squaresMap[capturedPawnPosition];

  std::vector<std::shared_ptr<Piece>> &opponentPieceVector = (pawn->getColor() == PieceColor::WHITE) ? blackPieces : whitePieces;
  std::vector<std::shared_ptr<Piece>> &opponentCapturedPieceVector = (pawn->getColor() == PieceColor::WHITE) ? blackCapturedPieces : whiteCapturedPieces;

  squaresMap[pawnEndingPosition] = pawn;
  squaresMap[pawnStartingPosition] = GameManager::makePiece(0, pawnStartingPosition);
  squaresMap[capturedPawnPosition] = GameManager::makePiece(0, capturedPawnPosition);

  std::shared_ptr<Piece> &friendKing = (pawn->getColor() == PieceColor::WHITE) ? whiteKing : blackKing;
  opponentPieceVector.erase(std::find(opponentPieceVector.begin(), opponentPieceVector.end(), capturedPawn));

  // Valid move case
  if (!isSquareAttacked(friendKing->getPosition(), !(pawn->getColor())))
  {
    pawn->move(pawnEndingPosition);
    opponentCapturedPieceVector.push_back(capturedPawn);
    this->incrementMoveNumber();
    return;
  }

  // Invalid move case. Resetting the board.
  opponentPieceVector.push_back(capturedPawn);
  squaresMap[pawnStartingPosition] = pawn;
  squaresMap[pawnEndingPosition] = GameManager::makePiece(0, pawnEndingPosition);
  squaresMap[capturedPawnPosition] = capturedPawn;
  throw InvalidMoveException("This move is not allowed. The king would be in check.");
}

/**
 *
 */
std::shared_ptr<Piece> Board::getPiece(const Coordinate position) const
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
  whiteCapturedPieces.clear();
  blackCapturedPieces.clear();
  whiteKing = nullptr;
  blackKing = nullptr;
  this->resetMoveNumber();
  for (int row = 1; row < 9; row++)
  {
    for (int column = 1; column < 9; column++)
    {
      Coordinate position(column, row);
      squaresMap[position] = GameManager::makePiece(0, position);
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

std::string Board::getWhiteCapturedPieces(const bool literal) const
{
  std::string piecesString;
  for (auto piece : whiteCapturedPieces)
  {
    piecesString += (piece->toString(literal) + " ");
  }
  return piecesString;
}

std::string Board::getBlackCapturedPieces(const bool literal) const
{
  std::string piecesString;
  for (auto piece : blackCapturedPieces)
  {
    piecesString += (piece->toString(literal) + " ");
  }
  return piecesString;
}
