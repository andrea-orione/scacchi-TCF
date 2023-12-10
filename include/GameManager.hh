#pragma once

#include <memory>
#include <string>
#include <vector>
#include <array>
#include <map>

#include "Piece.hh"

enum class PieceType
{
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
};

/**
 * Abstract GameManager for the creation of the pieces.
 */
class GameManager
{
public:
    GameManager() {}
    ~GameManager() {}

    void loadFenPosition(const std::string &fenString) const;

    std::shared_ptr<Piece> makePiece(const PieceType pType, const PieceColor pColor, const Coordinate &pPosition) const;
    std::shared_ptr<Piece> makePiece(char pieceChar, const Coordinate &pPosition) const;

private:
};
