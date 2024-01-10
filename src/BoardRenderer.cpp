#include "BoardRenderer.hh"

#include <stdexcept>
#include <string>
#include <vector>

void BoardRenderer::PrintBoard(PieceColor playerColor) const
{
  if (playerColor == PieceColor::VOID)
    throw std::invalid_argument("Board::PrintBoard() : The player color must be either black or white.");

  (playerColor == PieceColor::WHITE) ? this->PrintWhiteBoard() : this->PrintBlackBoard();
}

std::string_view BoardRenderer::PieceToString(const std::shared_ptr<Piece> piece) const
{
  if (piece->GetColor() == PieceColor::VOID) return " ";
  const auto &pieceChars = (piece->GetColor() == PieceColor::WHITE) ? whitePiecesChars : blackPiecesChars;
  return pieceChars.at(piece->GetType());
}

std::string BoardRenderer::PieceVectorToString(const std::vector<std::shared_ptr<Piece>> pieceVector) const
{
  std::string vectorString{};
  for (const auto piece : pieceVector)
  {
    vectorString += (std::string(this->PieceToString(piece)) + " ");
  }
  return vectorString;
}
