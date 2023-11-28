#pragma once

#include <memory>
#include <vector>

#include "Piece.hh"
#include "Bishop.hh"

using std::make_unique;
using std::unique_ptr;
using std::vector;

/**
 * Abstract factory for the creation of the pieces.
 */
class AbstractFactory
{
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
    /**
     * Create a vector of white pieces.
     *
     * @return A vector with unique pointers to the white pieces.
     */
    virtual vector<unique_ptr<Piece>> createPieces();
};

/**
 * Concrete factory for the creation of black pieces.
 */
class BlackFactory : public AbstractFactory
{
public:
    /**
     * Create a vector of black pieces.
     *
     * @return A vector with unique pointers to the white pieces.
     */
    virtual vector<unique_ptr<Piece>> createPieces();
};

/**
 * Concrete factory for the creation of empty pieces.
 */
class EmptyFactory : public AbstractFactory
{
public:
    /**
     * Create a vector of empty pieces.
     *
     * @return A vector with unique pointers to the white pieces.
     */
    virtual vector<unique_ptr<Piece>> createPieces();
};
