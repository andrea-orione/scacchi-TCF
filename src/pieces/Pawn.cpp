#include "Pawn.hh"
#include "Rook.hh"
#include "Board.hh"
#include "Coordinate.hh"
#include "Movement.hh"
#include "Piece.hh"
#include <memory>
#include <stdexcept>

Pawn::Pawn(PieceColor pColor, Coordinate pPosition)
{
  color = pColor;
  position = pPosition;
  switch (color)
  {
  case PieceColor::WHITE:
    character = "♟︎";
    literalCharacter = 'P';
    break;
  case PieceColor::BLACK:
    character = "♙";
    literalCharacter = 'p';
    break;
  default:
    break;
  }
}

bool Pawn::isWhiteMoveValid(const Coordinate &endingwPosition) const
{
    const int xDistance = endingwPosition.getX() - this->position.getX();
    const int yDistance = endingwPosition.getY() - this->position.getY();
    
    if (this->position.getX() == 2)
    {
        if (yDistance > 2 || yDistance < 1 || xDistance > 1)
            return false;
    }
    if (this->position.getX() != 2)
    {
        if (yDistance != 1 || xDistance > 1)
            return false;
    }

    // mossa

    Board& board = Board::Instance();

    // Check if landing square is free

    std::shared_ptr<Piece> endingPositionPiece = board.getPiece(endingwPosition);
    if (endingPositionPiece != nullptr)
        if (endingPositionPiece->getColor() == this->color)
            return false;

  return true;
}

bool Pawn::isBlackMoveValid(const Coordinate& endingbPosition) const
{
    const int xDistance = endingbPosition.getX() - this->position.getX();
    const int yDistance = endingbPosition.getY() - this->position.getY();

    if (this->position.getX() == 7)
    {
        if (yDistance < -2 && yDistance > -1 && xDistance > 1)
            return false;
    }
    if (this->position.getX() != 7)
    {
        if (yDistance != -1 || xDistance > 1)
            return false;
    }

    // mossa

    Board& board = Board::Instance();

    // Check if landing square is free

    std::shared_ptr<Piece> endingPositionPiece = board.getPiece(endingbPosition);
    if (endingPositionPiece != nullptr)
        if (endingPositionPiece->getColor() == this->color)
            return false;

    return true;
}

bool Pawn::isMoveValid(const Coordinate& endingposition) const
{
    if (color == PieceColor::BLACK)
    {
        return Pawn::isBlackMoveValid(endingposition);
    }
    return Pawn::isWhiteMoveValid(endingposition);
}


std::string Pawn::toString(bool literal) const
{
  if (literal)
    return std::string(1, literalCharacter);
  return character;
}
