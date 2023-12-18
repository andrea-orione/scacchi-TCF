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

std::string Knight::toString(bool literal) const
{
  if (literal)
    return std::string(1, literalCharacter);
  return character;
}

bool Knight::isMoveValid(const Coordinate endingPosition) const
{
  int xDistance = endingPosition.getX() - this->position.getX();
  int yDistance = endingPosition.getY() - this->position.getY();

  // geometric check
  if (this->position.squaredDistance(endingPosition) != 5)
    return false;

  // determine if the move is valid
  Board &board = Board::Instance();
  std::shared_ptr<Piece> endingPiece = board.getPiece(endingPosition);

  return !(endingPiece->getColor() == this->color);
}
