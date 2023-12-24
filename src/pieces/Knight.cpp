#include "Knight.hh"

#include "Board.hh"
#include "Piece.hh"

Knight::Knight(PieceColor pColor, Coordinate pPosition)
{
  pieceType = PieceType::KNIGHT;
  color = pColor;
  position = pPosition;
  switch (color)
  {
  case PieceColor::WHITE:
    character = "♞";
    literalCharacter = 'N';
    break;
  case PieceColor::BLACK:
    character = "♘";
    literalCharacter = 'n';
    break;
  default:
    break;
  }
}

std::string Knight::ToString(bool simplified) const
{
  if (simplified)
    return std::string(1, literalCharacter);
  return character;
}

bool Knight::IsMoveValid(const Coordinate endingPosition) const
{
  int xDistance = endingPosition.GetX() - this->position.GetX();
  int yDistance = endingPosition.GetY() - this->position.GetY();

  // geometric check
  if (this->position.SquaredDistance(endingPosition) != 5)
    return false;

  // determine if the move is valid
  Board &board = Board::Instance();
  std::shared_ptr<Piece> endingPiece = board.GetPiece(endingPosition);

  return !(endingPiece->GetColor() == this->color);
}
