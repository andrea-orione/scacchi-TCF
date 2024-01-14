#include "Board.hh"

#include <algorithm>
#include <cctype>
#include <memory>
#include <tuple>
#include <vector>

#include "BoardFactory.hh"
#include "Coordinate.hh"
#include "Movement.hh"
#include "Utils.hh"
#include "Piece.hh"

/**
 * The default constructor.
 *
 * It creates the 64 squares.
 */
Board::Board() : squaresMap{},
                 whitePieces{},
                 blackPieces{},
                 whiteCapturedPieces{},
                 blackCapturedPieces{},
                 whiteKing(nullptr),
                 blackKing(nullptr)
{
  for (int row = 1; row < 9; row++)
  {
    for (int column = 1; column < 9; column++)
    {
      const Coordinate position(column, row);
      squaresMap.insert(std::make_pair(position, BoardFactory::MakePiece(0, position)));
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
 * Function for updating the `squaresMap`.
 *
 * @param[in] square The `std::pair` representing the square (see `squaresMap`).
 */
void Board::UpdateSquare(Coordinate position, std::shared_ptr<Piece> piece)
{
  this->squaresMap.at(position) = piece;
}

/**
 * Function for adding pieces to the `whitePieces` and `blackPieces` vectors.
 */
void Board::UpdatePiecesVector()
{
  this->whitePieces.clear();
  this->blackPieces.clear();
  for (const auto [coordinate, piece] : this->squaresMap)
  {
    if (piece->GetColor() == PieceColor::BLACK)
      this->blackPieces.push_back(piece);
    else if (piece->GetColor() == PieceColor::WHITE)
      this->whitePieces.push_back(piece);
  }
}

/**
 * Function for updating the data members `whiteKing` and `blackKing`.
 */
void Board::AddKings(const Coordinate whiteKingPosition, const Coordinate blackKingPosition)
{
  this->whiteKing = GetPiece(whiteKingPosition);
  this->blackKing = GetPiece(blackKingPosition);
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
  auto &playerPieces = (playerColor == PieceColor::WHITE) ? this->whitePieces : this->blackPieces;
  auto &opponentPieces = (playerColor == PieceColor::WHITE) ? this->blackPieces : this->whitePieces;
  const auto &friendKing = (playerColor == PieceColor::WHITE) ? this->whiteKing : this->blackKing;

  for (const auto [coordinate, occupyingPiece] : this->squaresMap)
  {
    if (occupyingPiece->GetColor() == playerColor)
      continue;

    for (const auto piece : playerPieces)
    {
      try
      {
        if (!piece->IsMoveValid(coordinate))
          continue;
      }
      catch (CastlingSignal)
      {
        continue;
      }
      catch (EnPassantSignal)
      {
        continue;
      }

      // Setting up the position to be tested
      const Coordinate startingPosition = piece->GetPosition();
      std::shared_ptr<Piece> temporaryStorageCapturedPiece = occupyingPiece;
      squaresMap.at(coordinate) = piece;
      squaresMap.at(startingPosition) = BoardFactory::MakePiece(0, startingPosition);
      const Coordinate friendKingPosition = (friendKing == piece) ? coordinate : friendKing->GetPosition();
      if (temporaryStorageCapturedPiece->GetColor() != PieceColor::VOID)
        opponentPieces.erase(std::find(opponentPieces.begin(), opponentPieces.end(), temporaryStorageCapturedPiece));

      // Checking if the position is valid
      const bool isCheck = IsSquareAttacked(friendKingPosition, !playerColor);

      // Resetting the board.
      if (temporaryStorageCapturedPiece->GetColor() != PieceColor::VOID)
        opponentPieces.push_back(temporaryStorageCapturedPiece);
      squaresMap.at(startingPosition) = piece;
      squaresMap.at(coordinate) = temporaryStorageCapturedPiece;

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
  const auto &attackerVector = (attackerColor == PieceColor::WHITE) ? this->whitePieces : this->blackPieces;
  for (const auto attackingPiece : attackerVector)
  {
    if (attackingPiece->IsMoveValid(square))
      return true;
  }
  return false;
}

/**
 * Function for checking if a move is valid and, in that case, updating the board and the internal position of the piece.
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
  auto &opponentPieceVector = (movingPiece->GetColor() == PieceColor::WHITE) ? blackPieces : whitePieces;
  auto &opponentCapturedPieceVector = (movingPiece->GetColor() == PieceColor::WHITE) ? blackCapturedPieces : whiteCapturedPieces;
  std::shared_ptr<Piece> temporaryStorageCapturedPiece = squaresMap.at(endingPosition);
  squaresMap.at(endingPosition) = movingPiece;
  squaresMap.at(startingPosition) = BoardFactory::MakePiece(0, startingPosition);
  std::shared_ptr<Piece> &friendKing = (movingPiece->GetColor() == PieceColor::WHITE) ? whiteKing : blackKing;
  const Coordinate &friendKingPosition = (friendKing == movingPiece) ? endingPosition : friendKing->GetPosition();
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
  squaresMap.at(startingPosition) = movingPiece;
  squaresMap.at(endingPosition) = temporaryStorageCapturedPiece;
  throw InvalidMoveException("This move is not allowed. The king would be in check.");
}

/**
 * Function for promoting a pawn.
 */
void Board::Promotion(std::shared_ptr<Piece> &&pawn, const char promotionPiece, const Coordinate endingPosition)
{
  if (!pawn->IsMoveValid(endingPosition))
    throw InvalidMoveException("This move is not allowed. This piece cannot reach that position.");

  // promote to the right color
  const char newPieceChar = (pawn->GetColor() == PieceColor::WHITE) ? std::toupper(promotionPiece) : std::tolower(promotionPiece);
  std::shared_ptr<Piece> newPiece = BoardFactory::MakePiece(newPieceChar, endingPosition);

  const Coordinate startingPosition = pawn->GetPosition();
  std::shared_ptr<Piece> capturedPiece = squaresMap.at(endingPosition);
  auto &opponentPieceVector = (pawn->GetColor() == PieceColor::WHITE) ? blackPieces : whitePieces;
  auto &opponentCapturedPieceVector = (pawn->GetColor() == PieceColor::WHITE) ? blackCapturedPieces : whiteCapturedPieces;
  squaresMap.at(endingPosition) = newPiece;
  squaresMap.at(startingPosition) = BoardFactory::MakePiece(0, startingPosition);
  const Coordinate friendKingPosition = (pawn->GetColor() == PieceColor::WHITE) ? whiteKing->GetPosition() : blackKing->GetPosition();
  if (capturedPiece->GetColor() != PieceColor::VOID)
    opponentPieceVector.erase(std::find(opponentPieceVector.begin(), opponentPieceVector.end(), capturedPiece));

  // Valid move case
  if (!IsSquareAttacked(friendKingPosition, !(pawn->GetColor())))
  {
    pawn->Move(endingPosition);
    if (capturedPiece->GetType() != PieceType::VOID)
      opponentCapturedPieceVector.push_back(capturedPiece);
    return;
  }

  // Invalid move case. Resetting the board.
  if (capturedPiece->GetColor() != PieceColor::VOID)
    opponentPieceVector.push_back(capturedPiece);
  squaresMap.at(startingPosition) = pawn;
  squaresMap.at(endingPosition) = capturedPiece;
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
  if (IsSquareAttacked(kingStartingPosition, !(king->GetColor())))
    throw InvalidMoveException("Castling is not allowed. The king is in check.");

  const int rookY = kingStartingPosition.GetY();
  const Coordinate rookStartingPosition = (kingEndingPosition.GetX() == 7) ? Coordinate(8, rookY) : Coordinate(1, rookY);
  const Coordinate rookEndingPosition = (kingEndingPosition.GetX() == 7) ? Coordinate(6, rookY) : Coordinate(4, rookY);
  squaresMap.at(kingEndingPosition) = squaresMap.at(kingStartingPosition);
  squaresMap.at(rookEndingPosition) = squaresMap.at(rookStartingPosition);
  squaresMap.at(kingStartingPosition) = BoardFactory::MakePiece(0, kingStartingPosition);
  squaresMap.at(rookStartingPosition) = BoardFactory::MakePiece(0, rookStartingPosition);

  if (!(IsSquareAttacked(kingEndingPosition, !(king->GetColor())) || IsSquareAttacked(rookEndingPosition, !(king->GetColor()))))
  {
    squaresMap.at(kingEndingPosition)->Move(kingEndingPosition);
    squaresMap.at(rookEndingPosition)->Move(rookEndingPosition);
    return;
  }

  squaresMap.at(kingStartingPosition) = squaresMap.at(kingEndingPosition);
  squaresMap.at(rookStartingPosition) = squaresMap.at(rookEndingPosition);
  squaresMap.at(kingEndingPosition) = BoardFactory::MakePiece(0, kingEndingPosition);
  squaresMap.at(rookEndingPosition) = BoardFactory::MakePiece(0, rookEndingPosition);
  throw InvalidMoveException("Castling is not allowed. The king cannot pass through or end in check.");
}

/**
 * Function for checking if an en-passant move is valid and, in that case, updating the board and the internal position of the piece.
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

  auto &opponentPieceVector = (pawn->GetColor() == PieceColor::WHITE) ? blackPieces : whitePieces;
  auto &opponentCapturedPieceVector = (pawn->GetColor() == PieceColor::WHITE) ? blackCapturedPieces : whiteCapturedPieces;

  squaresMap.at(pawnEndingPosition) = pawn;
  squaresMap.at(pawnStartingPosition) = BoardFactory::MakePiece(0, pawnStartingPosition);
  squaresMap.at(capturedPawnPosition) = BoardFactory::MakePiece(0, capturedPawnPosition);

  const std::shared_ptr<Piece> &friendKing = (pawn->GetColor() == PieceColor::WHITE) ? whiteKing : blackKing;
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
  squaresMap.at(pawnStartingPosition) = pawn;
  squaresMap.at(pawnEndingPosition) = BoardFactory::MakePiece(0, pawnEndingPosition);
  squaresMap.at(capturedPawnPosition) = capturedPawn;
  throw InvalidMoveException("This move is not allowed. The king would be in check.");
}

/**
 * Function for determining if there is enough material to continue the game.
 *
 * This function checks for the following configurations:
 *  - king vs king;
 *  - king vs king + knight;
 *  - king vd king + bishop.
 *
 * None of these can lead to a checkmate, so the game is stopped.
 *
 * @return true if the position is a stale by lack of material, false otherwise.
 */
bool Board::IsMaterialLacking() const
{
  int knightOrBishopCounter = 0;

  for (const auto piece : whitePieces)
  {
    if (piece->GetType() == PieceType::KNIGHT || piece->GetType() == PieceType::BISHOP)
      knightOrBishopCounter++;
    if ((piece->GetType() != PieceType::KNIGHT && piece->GetType() != PieceType::KING && piece->GetType() != PieceType::BISHOP) || knightOrBishopCounter > 1)
      return false;
  }
  for (const auto piece : blackPieces)
  {
    if (piece->GetType() == PieceType::KNIGHT || piece->GetType() == PieceType::BISHOP)
      knightOrBishopCounter++;
    if ((piece->GetType() != PieceType::KNIGHT && piece->GetType() != PieceType::KING && piece->GetType() != PieceType::BISHOP) || knightOrBishopCounter > 1)
      return false;
  }
  return true;
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
      squaresMap[position] = BoardFactory::MakePiece(0, position);
    }
  }
}

/**
 * Function for getting a string containing the white/black captured pieces.
 *
 * @param[in] literal A bool indicating if the pieces should be returned as letter (instead of UNICODE chars).
 *
 * @return The aforementioned string
 */
std::vector<std::shared_ptr<Piece>> Board::GetCapturedPieces(PieceColor pColor) const
{
  if (pColor == PieceColor::VOID)
    throw std::invalid_argument("Board::GetCapturedPieces() : The captured pieces must be either white or black.");

  return (pColor == PieceColor::WHITE) ? whiteCapturedPieces : blackCapturedPieces;
}

/**
 * Function for getting a string_view representing the board state.
 *
 * @return The aforementioned string_view
 */
std::string Board::GetFenPosition() const
{
  std::string cycleString;

  for (int i = 8; i >= 1; i--)
  {
    for (int j = 1; j <= 8; j++)
    {
      std::shared_ptr<Piece> cPiece = squaresMap.at(Coordinate(j, i));
      const char pString = cPiece->GetChar();
      cycleString.push_back(pString);
    }
  }

  return cycleString;
}
