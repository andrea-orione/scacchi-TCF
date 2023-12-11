#include "Bishop.hh"

#include <memory>
#include <stdexcept>

#include "Movement.hh"
#include "Board.hh"

Bishop::Bishop(PieceColor pColor, Coordinate pPosition)
{
  color = pColor;
  position = pPosition;
  switch (color)
  {
  case PieceColor::WHITE:
    character = "♝";
    literalCharacter = 'B';
    break;
  case PieceColor::BLACK:
    character = "♗";
    literalCharacter = 'b';
    break;
  default:
    break;
  }
}

std::string Bishop::toString(bool literal) const
{
  if (literal)
    return std::string(1, literalCharacter);
  return character;
}

bool Bishop::isMoveValid(const Coordinate &startingPosition, const Coordinate &endingPosition) const
{
  int xDistance = endingPosition.getX() - startingPosition.getX();
  int yDistance = endingPosition.getY() - startingPosition.getY();

  // geometric check
  if (abs(xDistance) != abs(yDistance))
    return false;

  // determine diagonal
  Movement baseMove = Movement(xDistance / abs(xDistance), yDistance / abs(yDistance));

  // determine if the move is valid valid
  Board &board = Board::Instance();
  std::shared_ptr<Piece> mainPiece = board.getPiece(startingPosition);

  for (int i = 0; i < xDistance; i++)
  {
    const Coordinate newPosition = startingPosition + baseMove * i;
    std::shared_ptr<Piece> newPiece = board.getPiece(newPosition);

    if (newPiece != nullptr)
    {
      if (newPosition == endingPosition && newPiece->getColor() != mainPiece->getColor())
        return true;

      return false;
    }
  }
  return true;
}