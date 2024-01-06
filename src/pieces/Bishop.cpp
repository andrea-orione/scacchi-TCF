#include "Bishop.hh"

#include <memory>

#include "Movement.hh"
#include "Board.hh"
#include "Piece.hh"
#include "Utils.hh"

Bishop::Bishop(PieceColor pColor, Coordinate pPosition)
{
  pieceType = PieceType::BISHOP;
  color = pColor;
  position = pPosition;
  switch (color)
  {
  case PieceColor::WHITE:
    character = "♝";
    coloredCharacter = "♗";
    literalCharacter = 'B';
    break;
  case PieceColor::BLACK:
    character = "♗";
    coloredCharacter = "♝";
    literalCharacter = 'b';
    break;
  default:
    break;
  }
}

std::string Bishop::ToString(bool simplified, bool colored) const
{
  if (simplified)
    return std::string(1, literalCharacter);
  if (colored)
    return coloredCharacter;
  return character;
}

bool Bishop::IsMoveValid(const Coordinate endingPosition) const
{
  const int xDistance = endingPosition.GetX() - this->position.GetX();
  const int yDistance = endingPosition.GetY() - this->position.GetY();

  // geometric check
  if (abs(xDistance) != abs(yDistance))
    return false;

  // determine diagonal
  Movement baseMove(utils::sgn(xDistance), utils::sgn(yDistance));

  // determine if the move is valid
  Board &board = Board::Instance();
  std::shared_ptr<Piece> endingPositionPiece = board.GetPiece(endingPosition);
  if (endingPositionPiece->GetColor() == this->color)
    return false;

  // Check whether there are other pieces in the way.
  for (Coordinate newPosition = this->GetPosition() + baseMove; newPosition != endingPosition; newPosition += baseMove)
  {
    if (board.GetPiece(newPosition)->GetColor() != PieceColor::VOID)
      return false;
  }
  return true;
}
