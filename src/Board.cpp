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
Board::Board() : squaresMap({}),
                 whitePieces({}),
                 blackPieces({}),
                 whiteCapturedPieces({}),
                 blackCapturedPieces({}),
                 whiteKing(nullptr),
                 blackKing(nullptr)
{
  for (int row = 1; row < 9; row++)
  {
    for (int column = 1; column < 9; column++)
    {
      Coordinate position(column, row);
      squaresMap.insert(std::make_pair(position, GameManager::MakePiece(0, position)));
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
 * Prints the state of the board and the captured pieces from the white perspective.
 *
 * It displays visually to the screen the board using UNICODE characters.
 *
 * @param[in] simplified Whether to use simplified chars or not. `false` by default.
 */
void Board::PrintWhiteBoard(bool simplified) const
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
      cout << piecePtr->ToString(simplified);

      // Slightly inefficient but makes the code cleaner
      if (column != 8)
        cout << " " << separator << " ";
      else
        cout << " " << border;
    }
    if (row == 8)
      cout << "   BLACK CAPTURED PIECES: " << GetBlackCapturedPieces(simplified);
    if (row == 7)
      cout << "   WHITE CAPTURED PIECES: " << GetWhiteCapturedPieces(simplified);
    if (row != 1)
      cout << "\n   " << middle << "\n";
    else
      cout << "\n   " << bottom << "\n";
  }
  cout << "     a   b   c   d   e   f   g   h\n"
       << endl;
}

/**
 * Prints the state of the board and the captured pieces from the black perspective.
 *
 * It displays visually to the screen the board using UNICODE characters.
 *
 * @param[in] simplified Whether to use simplified chars or not. `false` by default.
 */
void Board::PrintBlackBoard(bool simplified) const
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
      cout << piecePtr->ToString(simplified);

      // Slightly inefficient but makes the code cleaner
      if (column != 1)
        cout << " " << separator << " ";
      else
        cout << " " << border;
    }
    if (row == 1)
      cout << "   BLACK CAPTURED PIECES: " << GetBlackCapturedPieces(simplified);
    if (row == 2)
      cout << "   WHITE CAPTURED PIECES: " << GetWhiteCapturedPieces(simplified);
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
void Board::UpdateSquare(std::pair<Coordinate, std::shared_ptr<Piece>> &&square) noexcept
{
  squaresMap[square.first] = square.second;
}

/**
 * Function for adding pieces to the `whitePieces` and `blackPieces` vectors.
 *
 * @param[in] newPiece The pointer to the piece to be added.
 */
void Board::UpdatePiecesVector()
{
  for (auto iterator = squaresMap.begin(); iterator != squaresMap.end(); iterator++)
  {
    if (iterator->second->GetColor() == PieceColor::BLACK)
      blackPieces.push_back(iterator->second);
    else if (iterator->second->GetColor() == PieceColor::WHITE)
      whitePieces.push_back(iterator->second);
  }
}

/**
 * Function for updating the data members `whiteKing` and `blackKing`.
 */
void Board::AddKings(const Coordinate whiteKingPosition, const Coordinate blackKingPosition)
{
  whiteKing = GetPiece(whiteKingPosition);
  blackKing = GetPiece(blackKingPosition);
}

/**
 * Function for determining if the king of the given color is in check.
 *
 * @param[in] kingColor the color of the king.
 *
 * @return true if the king is in check, false otherwise.
 */
bool Board::IsKingInCheck(const PieceColor kingColor) const
{
  const Coordinate kingPosition = (kingColor == PieceColor::WHITE) ? this->whiteKing->GetPosition() : this->blackKing->GetPosition();
  return this->IsSquareAttacked(kingPosition, !kingColor);
}

/**
 * Function for determining if one player has valid moves.
 * Checks if any friend piece can move in any square so that the friend king isn't in check.
 *
 * @param[in] playerColor The color of the color of the player to be checked.
 *
 * @return true if the player has valid moves, false otherwise.
 */
bool Board::HasValidMoves(const PieceColor playerColor)
{
  std::vector<std::shared_ptr<Piece>> &playerPieces = (playerColor == PieceColor::WHITE) ? whitePieces : blackPieces;
  std::vector<std::shared_ptr<Piece>> &opponentPieces = (playerColor == PieceColor::WHITE) ? blackPieces : whitePieces;
  std::shared_ptr<Piece> &friendKing = (playerColor == PieceColor::WHITE) ? whiteKing : blackKing;
  for (auto [coordinate, occupyingPiece] : this->squaresMap)
  {
    if (occupyingPiece->GetColor() == playerColor)
      continue;
    for (auto piece : playerPieces)
    {
      if (!piece->IsMoveValid(coordinate))
        continue;

      // Setting up the position to be tested
      const Coordinate startingPosition = piece->GetPosition();
      std::shared_ptr<Piece> temporaryStorageCapturedPiece = occupyingPiece;
      squaresMap[coordinate] = piece;
      squaresMap[startingPosition] = GameManager::MakePiece(0, startingPosition);
      const Coordinate friendKingPosition = (friendKing == piece) ? coordinate : friendKing->GetPosition();
      if (temporaryStorageCapturedPiece->GetColor() != PieceColor::VOID)
        opponentPieces.erase(std::find(opponentPieces.begin(), opponentPieces.end(), temporaryStorageCapturedPiece));

      // Checking if the position is valid
      const bool isCheck = IsSquareAttacked(friendKingPosition, !playerColor);

      // Resetting the board.
      if (temporaryStorageCapturedPiece->GetColor() != PieceColor::VOID)
        opponentPieces.push_back(temporaryStorageCapturedPiece);
      squaresMap[startingPosition] = piece;
      squaresMap[coordinate] = temporaryStorageCapturedPiece;

      if (!isCheck)
        return true;
    }
  }
  return false;
}

/**
 * Function for determining whether a square is attacked (reachable) by the pieces of one color.
 *
 * @param[in] square The coordinate to the square to be checked.
 * @param[in] attackerColor The color of the pieces that can attack the square.
 *
 * @return `true` if the square is reachable,`false` otherwise.
 */
bool Board::IsSquareAttacked(const Coordinate square, const PieceColor attackerColor) const
{
  const std::vector<std::shared_ptr<Piece>> &attackerVector = (attackerColor == PieceColor::WHITE) ? whitePieces : blackPieces;
  for (auto attackingPiece : attackerVector)
  {
    if (attackingPiece->IsMoveValid(square))
      return true;
  }
  return false;
}

/**
 * Function for checking if a move is valid and, in that case, updating the board and the internal position of the piece.
 *
 * @todo Farei un diagramma di flusso piuttosto che un poema.
 *
 * The function first checks whether the piece can reach the endingPosition.
 * Then updates temporarily the board storing the eventual captured piece in a temporary variable.
 * It checks if in the new position the king of the movingColor is under check.
 * In that case the move is invalid, so the previous position is restored and an error is thrown.
 * Otherwise the move is valid, so the internal position of the moving piece is updated,
 * and the eventual captured piece is stored into the capturedPieces vector of the opposing team.
 * If the move is a castle or en-passant, an exception is thrown by the `IsMoveValid` method of the moving piece.
 * In that case the exception is caught and the validity check is delegated to the proper methods.
 *
 * @param[in] movingPiece A pointer to the piece that should move.
 * @param[in] endingPosition The coordinate of the square that should be reached.
 */
void Board::NormalMove(std::shared_ptr<Piece> &&movingPiece, const Coordinate endingPosition)
{
  try
  {
    if (!(movingPiece->IsMoveValid(endingPosition)))
      throw InvalidMoveException("This move is not allowed. This piece cannot reach that position.");
  }
  catch (const CastlingSignal)
  {
    Castling(std::move(movingPiece), endingPosition);
    return;
  }
  catch (const EnPassantSignal)
  {
    EnPassant(std::move(movingPiece), endingPosition);
    return;
  }

  const Coordinate startingPosition = movingPiece->GetPosition();
  std::vector<std::shared_ptr<Piece>> &opponentPieceVector = (movingPiece->GetColor() == PieceColor::WHITE) ? blackPieces : whitePieces;
  std::vector<std::shared_ptr<Piece>> &opponentCapturedPieceVector = (movingPiece->GetColor() == PieceColor::WHITE) ? blackCapturedPieces : whiteCapturedPieces;
  std::shared_ptr<Piece> temporaryStorageCapturedPiece = squaresMap[endingPosition];
  squaresMap[endingPosition] = movingPiece;
  squaresMap[startingPosition] = GameManager::MakePiece(0, startingPosition);
  std::shared_ptr<Piece> &friendKing = (movingPiece->GetColor() == PieceColor::WHITE) ? whiteKing : blackKing;
  const Coordinate friendKingPosition = (friendKing == movingPiece) ? endingPosition : friendKing->GetPosition();
  if (temporaryStorageCapturedPiece->GetColor() != PieceColor::VOID)
    opponentPieceVector.erase(std::find(opponentPieceVector.begin(), opponentPieceVector.end(), temporaryStorageCapturedPiece));

  // Valid move case
  if (!IsSquareAttacked(friendKingPosition, !(movingPiece->GetColor())))
  {
    movingPiece->Move(endingPosition);
    if (temporaryStorageCapturedPiece->GetType() != PieceType::VOID)
      opponentCapturedPieceVector.push_back(temporaryStorageCapturedPiece);
    return;
  }

  // Invalid move case. Resetting the board.
  if (temporaryStorageCapturedPiece->GetColor() != PieceColor::VOID)
    opponentPieceVector.push_back(temporaryStorageCapturedPiece);
  squaresMap[startingPosition] = movingPiece;
  squaresMap[endingPosition] = temporaryStorageCapturedPiece;
  throw InvalidMoveException("This move is not allowed. The king would be in check.");
}

/**
 * Function for checking if a castling move is valid and, in that case, updating the board and the internal position of the piece.
 *
 * The function first checks whether if the king is in check or if he should pass through a check. In this case the move is invalid
 * Otherwise the move is valid, so the internal position of the moving piece is updated, and the rook is also moved.
 *
 * @param[in] king A pointer to the king that should move.
 * @param[in] kingEndingPosition The coordinate of the square that should be reached.
 */
void Board::Castling(std::shared_ptr<Piece> &&king, const Coordinate kingEndingPosition)
{
  // Preliminary control that the king isn't in check
  const Coordinate kingStartingPosition = king->GetPosition();
  if (IsSquareAttacked(kingStartingPosition, king->GetColor()))
    throw InvalidMoveException("Castling is not allowed. The king is in check.");

  const int rookY = kingStartingPosition.GetY();
  const Coordinate rookStartingPosition = (kingEndingPosition.GetX() == 7) ? Coordinate(8, rookY) : Coordinate(1, rookY);
  const Coordinate rookEndingPosition = (kingEndingPosition.GetX() == 7) ? Coordinate(6, rookY) : Coordinate(4, rookY);
  squaresMap[kingEndingPosition] = squaresMap[kingStartingPosition];
  squaresMap[rookEndingPosition] = squaresMap[rookStartingPosition];
  squaresMap[kingStartingPosition] = GameManager::MakePiece(0, kingStartingPosition);
  squaresMap[rookStartingPosition] = GameManager::MakePiece(0, rookStartingPosition);

  if (!(IsSquareAttacked(kingEndingPosition, king->GetColor()) && IsSquareAttacked(rookEndingPosition, king->GetColor())))
  {
    squaresMap[kingEndingPosition]->Move(kingEndingPosition);
    squaresMap[rookEndingPosition]->Move(rookEndingPosition);
    return;
  }

  squaresMap[kingStartingPosition] = squaresMap[kingEndingPosition];
  squaresMap[rookStartingPosition] = squaresMap[rookEndingPosition];
  squaresMap[kingEndingPosition] = GameManager::MakePiece(0, kingEndingPosition);
  squaresMap[rookEndingPosition] = GameManager::MakePiece(0, rookEndingPosition);
  throw InvalidMoveException("Castling is not allowed. The king cannot pass through or end in check.");
}

/**
 * Function for checking if an en-passant move is valid and, in that case, updating the board and the internal position of the piece.
 *
 * @todo Farei un diagramma di flusso piuttosto che un poema.
 *
 * The function updates temporarily the board storing the captured piece in a temporary variable.
 * It checks if in the new position the king of the movingColor is under check.
 * In that case the move is invalid, so the previous position is restored and an error is thrown.
 * Otherwise the move is valid, so the internal position of the moving piece is updated,
 * and the eventual captured piece is stored into the capturedPieces vector of the opposing team.
 * If the move is a castle or en-passant, an exception is thrown by the `IsMoveValid` method of the moving piece.
 * In that case the exception is caught and the validity check is delegated to the proper methods.
 *
 * @param[in] pawn A pointer to the pawn that should move.
 * @param[in] pawnEndingPosition The coordinate to the square that should be reached.
 */
void Board::EnPassant(std::shared_ptr<Piece> &&pawn, const Coordinate pawnEndingPosition)
{
  const Coordinate pawnStartingPosition = pawn->GetPosition();
  const Movement capturingMovement = (pawn->GetColor() == PieceColor::WHITE) ? Movement(0, -1) : Movement(0, 1);
  const Coordinate capturedPawnPosition = pawnEndingPosition + capturingMovement;

  std::shared_ptr<Piece> capturedPawn = squaresMap[capturedPawnPosition];

  std::vector<std::shared_ptr<Piece>> &opponentPieceVector = (pawn->GetColor() == PieceColor::WHITE) ? blackPieces : whitePieces;
  std::vector<std::shared_ptr<Piece>> &opponentCapturedPieceVector = (pawn->GetColor() == PieceColor::WHITE) ? blackCapturedPieces : whiteCapturedPieces;

  squaresMap[pawnEndingPosition] = pawn;
  squaresMap[pawnStartingPosition] = GameManager::MakePiece(0, pawnStartingPosition);
  squaresMap[capturedPawnPosition] = GameManager::MakePiece(0, capturedPawnPosition);

  std::shared_ptr<Piece> &friendKing = (pawn->GetColor() == PieceColor::WHITE) ? whiteKing : blackKing;
  opponentPieceVector.erase(std::find(opponentPieceVector.begin(), opponentPieceVector.end(), capturedPawn));

  // Valid move case
  if (!IsSquareAttacked(friendKing->GetPosition(), !(pawn->GetColor())))
  {
    pawn->Move(pawnEndingPosition);
    opponentCapturedPieceVector.push_back(capturedPawn);
    return;
  }

  // Invalid move case. Resetting the board.
  opponentPieceVector.push_back(capturedPawn);
  squaresMap[pawnStartingPosition] = pawn;
  squaresMap[pawnEndingPosition] = GameManager::MakePiece(0, pawnEndingPosition);
  squaresMap[capturedPawnPosition] = capturedPawn;
  throw InvalidMoveException("This move is not allowed. The king would be in check.");
}

/**
 * Function for determining if there is enough material to continue the game.
 *
 * If only the kings are left on the board, no player can checkmate the other, so the game is in stale.
 * This function checks if this is the case.
 * If just a knight (other than the kings) is left a checkmate is not possible eather.
 *
 * @return true if the position is a stale by lack of material, false otherwise.
 */
bool Board::IsMaterialLacking() const
{
  int knightCounter = 0;
  for (auto piece : whitePieces)
  {
    if (piece->GetType() == PieceType::KNIGHT)
      knightCounter++;
    if ((piece->GetType() != PieceType::KNIGHT && piece->GetType() != PieceType::KING) || knightCounter > 1)
      return false;
  }
  for (auto piece : blackPieces)
  {
    if (piece->GetType() == PieceType::KNIGHT)
      knightCounter++;
    if ((piece->GetType() != PieceType::KNIGHT && piece->GetType() != PieceType::KING) || knightCounter > 1)
      return false;
  }
  return true;
}

/**
 * The function for getting the piece in a given position.
 *
 * @param[in] position The coordinate to the square.
 *
 * @return A pointer to the piece in the square
 */
std::shared_ptr<Piece> Board::GetPiece(const Coordinate position) const
{
  return squaresMap.find(position)->second;
}

/**
 * Function for clearing the board.
 */
void Board::ClearBoard()
{
  whitePieces.clear();
  blackPieces.clear();
  whiteCapturedPieces.clear();
  blackCapturedPieces.clear();
  whiteKing = nullptr;
  blackKing = nullptr;
  this->ResetMoveNumber();
  for (int row = 1; row < 9; row++)
  {
    for (int column = 1; column < 9; column++)
    {
      Coordinate position(column, row);
      squaresMap[position] = GameManager::MakePiece(0, position);
    }
  }
}

/**
 * Function for getting a string containing the white captured pieces.
 *
 * @param[in] literal A bool indicating if the pieces should be returned as letter (instead of UNICODE chars).
 *
 * @return The aforementioned string
 */
std::string Board::GetWhiteCapturedPieces(const bool literal) const
{
  std::string piecesString;
  for (auto piece : whiteCapturedPieces)
  {
    piecesString += (piece->ToString(literal) + " ");
  }
  return piecesString;
}

/**
 * Function for getting a string containing the black captured pieces.
 *
 * @param[in] literal A bool indicating if the pieces should be returned as letter (instead of UNICODE chars).
 *
 * @return The aforementioned string
 */
std::string Board::GetBlackCapturedPieces(const bool literal) const
{
  std::string piecesString;
  for (auto piece : blackCapturedPieces)
  {
    piecesString += (piece->ToString(literal) + " ");
  }
  return piecesString;
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
    cout << piece->ToString() << " ";
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
    cout << piece->ToString() << " ";
  }
  cout << "\n";
}
