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
 * Function for determining whether a square is attacked (reachable) by the pieces of one color.
 * 
 * @param[in] square The coordinate to the square to be checked.
 * @param[in] attackerColor The color of the pieces that must be checke if can attack the square.
 *
 * @return true if the square is reachable, false otherwise.
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
 * Function for checking if a move is valid and in that case updating the board and the piece internal position.
 *
 * The funcion first checks whether the piece can reach the endingPosition.
 * Then updates temporarly the board storing the eventual captured piece in a temporary variable.
 * It checks if in the new position the king of the movingColor is under check.
 * In that case the move is invalid, so the preavious position is restored and an error is thrown.
 * Otherwise the move is valid, so the internal position of the moving piece is updated,
 * and the eventual captured piece is stored into the capturedPieces vector of the opposing team.
 * If the move is a castle or en-passant, an exeption is trown by the `isMoveValid` method of the moving piece.
 * In that case the exception is caught and the validity check is delegated to the proper methods.
 *
 * @param[in] movingPiece A pointer to the piece that should move.
 * @param[in] endingPosition The coordinate to the square that should be reached.
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
    return;
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
 * Function for checking if a castling move is valid and in that case updating the board and the piece internal position.
 *
 * The funcion first checks whether if the king is in check or if he should pass through a check. In this case the move is invalid
 * Otherwise the move is valid, so the internal position of the moving piece is updated, and the rook is also moved.
 *
 * @param[in] king A pointer to the king that should move.
 * @param[in] kingEndingPosition The coordinate to the square that should be reached.
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
    return;
  }

  squaresMap[kingStartingPosition] = squaresMap[kingEndingPosition];
  squaresMap[rookStartingPosition] = squaresMap[rookEndingPosition];
  squaresMap[kingEndingPosition] = GameManager::makePiece(0, kingEndingPosition);
  squaresMap[rookEndingPosition] = GameManager::makePiece(0, rookEndingPosition);
  throw InvalidMoveException("Castling is not allowed. The king cannot pass through or end in check.");
}

/**
 * Function for checking if an en-passant move is valid and in that case updating the board and the piece internal position.
 *
 * The funcion updates temporarly the board storing the captured piece in a temporary variable.
 * It checks if in the new position the king of the movingColor is under check.
 * In that case the move is invalid, so the preavious position is restored and an error is thrown.
 * Otherwise the move is valid, so the internal position of the moving piece is updated,
 * and the eventual captured piece is stored into the capturedPieces vector of the opposing team.
 * If the move is a castle or en-passant, an exeption is trown by the `isMoveValid` method of the moving piece.
 * In that case the exception is caught and the validity check is delegated to the proper methods.
 *
 * @param[in] pawn A pointer to the pawn that should move.
 * @param[in] pawnEndingPosition The coordinate to the square that should be reached.
 */
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
 * The function for getting the piece in a given position.
 *
 * @param[in] position The coordinate to the square.
 *
 * @return A pointer to the piece in the square
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

/**
 * A function for getting a string containing the white captured pieces.
 *
 * @param[in] literal A bool indicating if the pieces should be returned as letter (instead of UNICODE chars).
 *
 * @retun The aforementioned string
 */
std::string Board::getWhiteCapturedPieces(const bool literal) const
{
  std::string piecesString;
  for (auto piece : whiteCapturedPieces)
  {
    piecesString += (piece->toString(literal) + " ");
  }
  return piecesString;
}

/**
 * A function for getting a string containing the black captured pieces.
 *
 * @param[in] literal A bool indicating if the pieces should be returned as letter (instead of UNICODE chars).
 *
 * @retun The aforementioned string
 */
std::string Board::getBlackCapturedPieces(const bool literal) const
{
  std::string piecesString;
  for (auto piece : blackCapturedPieces)
  {
    piecesString += (piece->toString(literal) + " ");
  }
  return piecesString;
}
