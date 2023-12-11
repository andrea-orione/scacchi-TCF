#include "Knight.hh"

#include "Board.hh"

Knight::Knight(PieceColor pColor, Coordinate pPosition)
{
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

bool Knight::isMoveValid(const Coordinate &startingPosition, const Coordinate &endingPosition) const
{
  int xDistance = endingPosition.getX() - startingPosition.getX();
  int yDistance = endingPosition.getY() - startingPosition.getY();

  // geometric check
  if (startingPosition.squaredDistance(endingPosition) != 5)
    return false;

  // determine if the move is valid
  Board &board = Board::Instance();
  std::shared_ptr<Piece> mainPiece = board.getPiece(startingPosition);
  std::shared_ptr<Piece> endingPiece = board.getPiece(endingPosition);

  if (endingPiece != nullptr && endingPiece->getColor() == mainPiece->getColor())
    return false;

  return true;
}