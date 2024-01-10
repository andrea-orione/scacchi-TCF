#include "BoardRenderer.hh"

#include "Utils.hh"

#include <stdexcept>
#include <string>
#include <vector>

void BoardRenderer::PrintBoard(PieceColor playerColor) const
{
  if (playerColor == PieceColor::VOID)
    throw std::invalid_argument("Board::PrintBoard() : The player color must be either black or white.");

  (playerColor == PieceColor::WHITE) ? this->PrintWhiteBoard() : this->PrintBlackBoard();
}

std::string_view BoardRenderer::PieceToString(const std::shared_ptr<Piece> piece, const bool inverted) const
{
  if (piece->GetColor() == PieceColor::VOID) return " ";
  const PieceColor pieceColor = (inverted) ? !piece->GetColor() : piece->GetColor();
  const auto &pieceChars = (pieceColor == PieceColor::WHITE) ? whitePiecesChars : blackPiecesChars;
  return pieceChars.at(piece->GetType());
}

std::string BoardRenderer::PieceVectorToString(const std::vector<std::shared_ptr<Piece>> pieceVector, const bool inverted) const
{
  std::string vectorString{};
  for (const auto piece : pieceVector)
  {
    vectorString += (std::string(this->PieceToString(piece, inverted)) + " ");
  }
  return vectorString;
}
