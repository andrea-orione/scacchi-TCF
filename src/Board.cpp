#include "Board.hh"

#include <algorithm>
#include <memory>
#include <tuple>
#include <vector>

#include "BoardFactory.hh"
#include "Coordinate.hh"
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
std::unique_ptr<Piece> Board::ReplacePiece(Coordinate position, std::unique_ptr<Piece> piece)
{
  std::unique_ptr<Piece> occupyingPiece = std::move(squaresMap.at(position));
  if (occupyingPiece->GetColor() != PieceColor::VOID)
  {
    auto &occupyingPieceVector = (occupyingPiece->GetColor() == PieceColor::WHITE) ? whitePieces : blackPieces;
    occupyingPieceVector.erase(std::find(occupyingPieceVector.begin(), occupyingPieceVector.end(), occupyingPiece.get()));
  }
  if (piece->GetColor() != PieceColor::VOID)
  {
    auto &newPieceVector = (piece->GetColor() == PieceColor::WHITE) ? whitePieces : blackPieces;
    newPieceVector.push_back(piece.get());
  }
  this->squaresMap.at(position) = std::move(piece);
  return occupyingPiece;
}

std::unique_ptr<Piece> Board::RemovePiece(Coordinate position){
  std::unique_ptr<Piece> removedPiece = std::move(squaresMap.at(position));
  squaresMap.at(position) = BoardFactory::MakePiece(0, position);
  if (removedPiece->GetColor() != PieceColor::VOID)
  {
    auto &removedPieceVector = (removedPiece->GetColor() == PieceColor::WHITE) ? whitePieces : blackPieces;
    removedPieceVector.erase(std::find(removedPieceVector.begin(), removedPieceVector.end(), removedPiece.get()));
  }
  return removedPiece;
}

void Board::InsertPiece(Coordinate position, std::unique_ptr<Piece> piece){
  const Piece* occupyingPiece = GetPiece(position);
  if (occupyingPiece->GetColor() != PieceColor::VOID)
  {
    auto &occupyingPieceVector = (occupyingPiece->GetColor() == PieceColor::WHITE) ? whitePieces : blackPieces;
    occupyingPieceVector.erase(std::find(occupyingPieceVector.begin(), occupyingPieceVector.end(), occupyingPiece));
  }
  if (piece->GetColor() != PieceColor::VOID)
  {
    auto &newPieceVector = (piece->GetColor() == PieceColor::WHITE) ? whitePieces : blackPieces;
    newPieceVector.push_back(piece.get());
  }
  this->squaresMap.at(position) = std::move(piece);
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

  for (const auto &[coordinate, _] : this->squaresMap)
  {
    if (GetPiece(coordinate)->GetColor() == playerColor)
      continue;

    for (const auto piece : playerPieces)
    {
      const MoveType moveType = piece->IsMoveValid(coordinate);
      if (moveType == MoveType::INVALID)
        continue;

      // Setting up the position to be tested
      const Coordinate startingPosition = piece->GetPosition();
      std::unique_ptr<Piece> capturedPiece = ReplacePiece(coordinate, RemovePiece(startingPosition));
      const Coordinate friendKingPosition = (friendKing == piece) ? coordinate : friendKing->GetPosition();

      // Checking if the position is valid
      const bool isCheck = IsSquareAttacked(friendKingPosition, !playerColor);

      // Resetting the board.
      if (capturedPiece->GetColor() != PieceColor::VOID)
        opponentPieces.push_back(capturedPiece.get());
      InsertPiece(startingPosition, ReplacePiece(coordinate, std::move(capturedPiece)));

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
    if (attackingPiece->IsMoveValid(square) != MoveType::INVALID)
      return true;
  }
  return false;
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
std::vector<Piece*> Board::GetCapturedPieces(PieceColor pColor) const
{
  if (pColor == PieceColor::VOID)
    throw std::invalid_argument("Board::GetCapturedPieces() : The captured pieces must be either white or black.");

  const auto &capturedPieces = (pColor == PieceColor::WHITE) ? whiteCapturedPieces : blackCapturedPieces;
  std::vector<Piece*> result{capturedPieces.size()};
  for (auto &piece : capturedPieces)
  {
    result.push_back(piece.get());
  }
  return result;
}

/**
 * Function for adding a piece to the capturedPieces vector of the corresponding color.
 *
 * If the piece is void it does nothing.
 *
 * @param[in] piece The piece to be added.
 */
void Board::AddCapturedPiece(std::unique_ptr<Piece> piece)
{
  if (piece->GetColor() == PieceColor::VOID)
    return;
  auto &capturedVector = (piece->GetColor() == PieceColor::WHITE) ? whiteCapturedPieces : blackCapturedPieces;
  capturedVector.push_back(std::move(piece));
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
      const char pString = GetPiece(Coordinate(j, i))->GetChar();
      cycleString.push_back(pString);
    }
  }

  return cycleString;
}
