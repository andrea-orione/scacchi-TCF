#pragma once

#include <memory>
#include <vector>

#include "Piece.hh"

using std::make_unique;
using std::unique_ptr;
using std::vector;

/**
 * Abstract factory for the creation of the pieces.
 */
class AbstractFactory
{
protected:
    enum class Pieces
    {
        PAWN,
        BISHOP,
        KNIGHT,
        ROOK,
        QUEEN,
        KING
    };

public:
    AbstractFactory() {}
    virtual ~AbstractFactory() {}

    virtual vector<unique_ptr<Piece>> createPieces() = 0;
};

/**
 * Concrete factory for the creation of white pieces.
 */
class WhiteFactory : public AbstractFactory
{
public:
    virtual vector<unique_ptr<Piece>> createPieces();
};

/**
 * Concrete factory for the creation of black pieces.
 */
class BlackFactory : public AbstractFactory
{
public:
    virtual vector<unique_ptr<Piece>> createPieces();
};

/**
 * Concrete factory for the creation of empty pieces.
 */
class EmptyFactory : public AbstractFactory
{
public:
    virtual vector<unique_ptr<Piece>> createPieces();
};
