#include "Pawn.hh"
#include "Piece.hh"
#include "Board.hh"

Pawn::Pawn(PieceColor pColor, Coordinate pPosition)
{
  pieceType = PieceType::PAWN;
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

// Checks if the pawn move is diagonal; if false, the move is forward

bool Pawn::isBlackMoveDiag(const Coordinate& endingPosition) const
{
    const int xDistance = endingPosition.getX() - this->position.getX();
    const int yDistance = endingPosition.getY() - this->position.getY();

    if (yDistance == -1 && (xDistance == 1 || xDistance == -1))
        return true;

    return false;
}

bool Pawn::isWhiteMoveDiag(const Coordinate& endingPosition) const
{
    const int xDistance = endingPosition.getX() - this->position.getX();
    const int yDistance = endingPosition.getY() - this->position.getY();

    if (yDistance == +1 && (xDistance == 1 || xDistance == -1))
        return true;

    return false;
}

// Checks if the pawn move is valid

bool Pawn::isWhiteMoveValid(const Coordinate& endingwPosition) const
{
    const int xDistance = endingwPosition.getX() - this->position.getX();
    const int yDistance = endingwPosition.getY() - this->position.getY();

    if (this->position.getY() == 2)
    {
        if (yDistance > 2 || yDistance < 1 || xDistance > 1)
            return false;
    }
    if (this->position.getY() != 2)
    {
        if (yDistance != 1 || xDistance > 1)
            return false;
    }
    

    // Crea una scacchiera

    Board& board = Board::Instance();

    // Check if landing square is free

    std::shared_ptr<Piece> endingPositionPiece = board.getPiece(endingwPosition);
    
    if (Pawn::isWhiteMoveDiag(endingwPosition))
        if (endingPositionPiece->getColor() != PieceColor::BLACK)
            return false;
    if (endingPositionPiece != nullptr)
        if (endingPositionPiece->getColor() == this->color)
            return false;


    return true;
}

bool Pawn::isBlackMoveValid(const Coordinate& endingbPosition) const
{
    const int xDistance = endingbPosition.getX() - this->position.getX();
    const int yDistance = endingbPosition.getY() - this->position.getY();

    if (this->position.getY() == 7)
    {
        if (yDistance < -2 || yDistance > -1 && xDistance > 1)
            return false;
    }
    if (this->position.getY() != 7)
    {
        if (yDistance != -1 || xDistance > 1)
            return false;
    }

    // mossa

    Board& board = Board::Instance();

    // Check if landing square is free

    std::shared_ptr<Piece> endingPositionPiece = board.getPiece(endingbPosition);
    if (Pawn::isWhiteMoveDiag(endingbPosition))
        if (endingPositionPiece->getColor() != PieceColor::WHITE)
            return false;
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
