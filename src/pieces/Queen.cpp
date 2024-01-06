#include "Queen.hh"

#include <memory>

#include "Board.hh"
#include "Piece.hh"
#include "Utils.hh"

Queen::Queen(PieceColor pColor, Coordinate pPosition)
{
  pieceType = PieceType::QUEEN;
  color = pColor;
  position = pPosition;
  switch (color)
  {
  case PieceColor::WHITE:
    character = "♛";
    coloredCharacter = "♕";
    literalCharacter = 'Q';
    break;
  case PieceColor::BLACK:
    character = "♕";
    coloredCharacter = "♛";
    literalCharacter = 'q';
    break;
  default:
    break;
  }
}

std::string Queen::ToString(bool simplified, bool colored) const
{
  if (simplified)
    return std::string(1, literalCharacter);
  if (colored)
    return coloredCharacter;
  return character;
}

bool Queen::IsMoveValid(const Coordinate endingPosition) const
{
  const int xDistance = endingPosition.GetX() - this->position.GetX();
  const int yDistance = endingPosition.GetY() - this->position.GetY();

  // geometric check
  if (abs(xDistance) != abs(yDistance) && (xDistance != 0 && yDistance != 0))
    return false;

  // determine direction
  Movement baseMove(utils::sgn(xDistance), utils::sgn(yDistance));

  // determine if the move is valid
  Board &board = Board::Instance();

  // check final square
  std::shared_ptr<Piece> endingPositionPiece = board.GetPiece(endingPosition);
  if (endingPositionPiece->GetColor() == this->color)
    return false;

  // Check whether there are other pieces in the way.
  for (Coordinate newPosition = this->GetPosition() + baseMove; newPosition != endingPosition; newPosition += baseMove)
  {
    std::shared_ptr<Piece> newSquarePiece = board.GetPiece(newPosition);
    if (newSquarePiece->GetColor() != PieceColor::VOID)
      return false;
  }
  return true;
}
