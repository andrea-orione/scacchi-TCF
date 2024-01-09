#include "BoardRenderer.hh"
#include <stdexcept>

void BoardRenderer::PrintBoard(PieceColor playerColor) const {
  if (playerColor == PieceColor::VOID)
    throw std::invalid_argument("Board::PrintBoard() : The player color must be either black or white.");

  (playerColor == PieceColor::WHITE) ? this->PrintWhiteBoard() : this->PrintBlackBoard();
}
