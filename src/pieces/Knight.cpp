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
  std::cout << pPosition.getX() << std::endl;
}

std::string Knight::toString(bool literal) const
{
  if (literal)
    return std::string(1, literalCharacter);
  return character;
}

bool Knight::isMoveValid(const Coordinate &endingPosition) const
{
  int xDistance = endingPosition.getX() - this->position.getX();
  int yDistance = endingPosition.getY() - this->position.getY();
  std::cout << this->position.getX() <<std::endl;
  std::cout << xDistance << std::endl;
  std::cout << yDistance << std::endl;

  // geometric check
  if (this->position.squaredDistance(endingPosition) != 5)
  {std::cout << "Q1" << std::endl;
    return false;}

  // determine if the move is valid
  Board &board = Board::Instance();
  std::shared_ptr<Piece> endingPiece = board.getPiece(endingPosition);

  std::cout << "Q2" << std::endl;
  return !(endingPiece->getColor() == this->color);
}
