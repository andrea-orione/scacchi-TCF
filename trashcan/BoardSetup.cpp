/**
 * Structure containing the positions where to place the white pieces at the beginning of the game.
 */
struct WhiteMap
{
    const std::array<PieceType, 6> P_TYPE = {PieceType::PAWN,
                                             PieceType::ROOK,
                                             PieceType::KNIGHT,
                                             PieceType::BISHOP,
                                             PieceType::QUEEN,
                                             PieceType::KING};

    std::vector<std::pair<char, int>> ROOK = {{'a', 1}, {'h', 1}};
    std::vector<std::pair<char, int>> KNIGHT = {{'b', 1}, {'g', 1}};
    std::vector<std::pair<char, int>> BISHOP = {{'c', 1}, {'f', 1}};
    std::vector<std::pair<char, int>> KING = {{'e', 1}};
    std::vector<std::pair<char, int>> QUEEN = {{'d', 1}};
    std::vector<std::pair<char, int>> PAWN = {{'a', 2}, {'b', 2}, {'c', 2}, {'d', 2}, {'e', 2}, {'f', 2}, {'g', 2}, {'h', 2}};

    std::array<std::vector<std::pair<char, int>>, 6> COORD = {PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING};
};

/**
 * Structure containing the positions where to place the black pieces at the beginning of the game.
 */
struct BlackMap
{
    const std::array<PieceType, 6> P_TYPE = {PieceType::PAWN,
                                             PieceType::ROOK,
                                             PieceType::KNIGHT,
                                             PieceType::BISHOP,
                                             PieceType::QUEEN,
                                             PieceType::KING};

    std::vector<std::pair<char, int>> ROOK = {{'a', 8}, {'h', 8}};
    std::vector<std::pair<char, int>> KNIGHT = {{'b', 8}, {'g', 8}};
    std::vector<std::pair<char, int>> BISHOP = {{'c', 8}, {'f', 8}};
    std::vector<std::pair<char, int>> KING = {{'e', 8}};
    std::vector<std::pair<char, int>> QUEEN = {{'d', 8}};
    std::vector<std::pair<char, int>> PAWN = {{'a', 7}, {'b', 7}, {'c', 7}, {'d', 7}, {'e', 7}, {'f', 7}, {'g', 7}, {'h', 7}};

    std::array<std::vector<std::pair<char, int>>, 6> COORD = {PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING};
};

/**
 * Function for creating white pieces.
 *
 * It calls the Board (singleton) and updates its `std::map<Coordinate, Piece>`.
 */
void GameManager::createWhitePieces() const
{
    constexpr PieceColor pColor = PieceColor::WHITE;
    Board &boardInstance = Board::Instance();

    // get map of white pieces coordinates
    std::unique_ptr<WhiteMap> wm = std::make_unique<WhiteMap>();

    for (PieceType pt : wm->P_TYPE)
    {
        // explicitly convert PieceType to int
        int i = static_cast<std::underlying_type_t<PieceType>>(pt);

        for (std::pair<char, int> xy : wm->COORD[i])
        {
            Coordinate pPosition(xy.first, xy.second);
            auto piece = makePiece(pt, pColor, pPosition);
            boardInstance.updateSquare(std::make_pair(pPosition, piece));
            boardInstance.updateWhitePiecesVector(piece);
        }
    }
}

/**
 * Function for creating black pieces.
 *
 * It calls the Board (singleton) and updates its `std::map<Coordinate, Piece>`.
 */
void GameManager::createBlackPieces() const
{
    constexpr PieceColor pColor = PieceColor::BLACK;
    Board &boardInstance = Board::Instance();

    // get map of black pieces coordinates
    std::unique_ptr<BlackMap> wm = std::make_unique<BlackMap>();

    for (PieceType pt : wm->P_TYPE)
    {
        // explicitly convert PieceType to int
        int i = static_cast<std::underlying_type_t<PieceType>>(pt);

        for (std::pair<char, int> xy : wm->COORD[i])
        {
            Coordinate pPosition(xy.first, xy.second);
            auto piece = makePiece(pt, pColor, pPosition);
            boardInstance.updateSquare(std::make_pair(pPosition, piece));
            boardInstance.updateBlackPiecesVector(piece);
        }
    }
}

/**
 * Function for creating the pointer to a specified piece.
 *
 * @param[in] pType The type of the piece: `PieceType::PAWN`, `PieceType::ROOK`,
 * `PieceType::KNIGHT`, `PieceType::BISHOP`, `PieceType::QUEEN`, `PieceType::KING`.
 * @param[in] pColor The color of the piece: `PieceColor::BLACK`, `PieceColor::WHITE`.
 * @param[in] pPosition The position of the piece.
 *
 * @return The pointer to the piece that has been created created.
 */
std::shared_ptr<Piece> GameManager::makePiece(const PieceType pType, const PieceColor pColor, const Coordinate &pPosition) const
{
    switch (pType)
    {
    case PieceType::PAWN:
        return std::make_shared<Pawn>(pColor, pPosition);
        break;
    case PieceType::ROOK:
        return std::make_shared<Rook>(pColor, pPosition);
        break;
    case PieceType::KNIGHT:
        return std::make_shared<Knight>(pColor, pPosition);
        break;
    case PieceType::BISHOP:
        return std::make_shared<Bishop>(pColor, pPosition);
        break;
    case PieceType::QUEEN:
        return std::make_shared<Queen>(pColor, pPosition);
        break;
    case PieceType::KING:
        return std::make_shared<King>(pColor, pPosition);
        break;

    default:
        return nullptr;
    }
}

std::vector<std::string> testingVector = {"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
                                          "r6r/1b2k1bq/8/8/7B/8/8/R3K2R b KQ - 3 2",
                                          "8/8/8/2k5/2pP4/8/B7/4K3 b - d3 0 3",
                                          "r1bqkbnr/pppppppp/n7/8/8/P7/1PPPPPPP/RNBQKBNR w KQkq - 2 2",
                                          "r3k2r/p1pp1pb1/bn2Qnp1/2qPN3/1p2P3/2N5/PPPBBPPP/R3K2R b KQkq - 3 2",
                                          "2kr3r/p1ppqpb1/bn2Qnp1/3PN3/1p2P3/2N5/PPPBBPPP/R3K2R b KQ - 3 2",
                                          "rnb2k1r/pp1Pbppp/2p5/q7/2B5/8/PPPQNnPP/RNB1K2R w KQ - 3 9",
                                          "2r5/3pk3/8/2P5/8/2K5/8/8 w - - 5 4",
                                          "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8",
                                          "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10",
                                          "3k4/3p4/8/K1P4r/8/8/8/8 b - - 0 1",
                                          "8/8/4k3/8/2p5/8/B2P2K1/8 w - - 0 1",
                                          "8/8/1k6/2b5/2pP4/8/5K2/8 b - d3 0 1",
                                          "5k2/8/8/8/8/8/8/4K2R w K - 0 1",
                                          "3k4/8/8/8/8/8/8/R3K3 w Q - 0 1",
                                          "r3k2r/1b4bq/8/8/8/8/7B/R3K2R w KQkq - 0 1",
                                          "r3k2r/8/3Q4/8/8/5q2/8/R3K2R b KQkq - 0 1",
                                          "2K2r2/4P3/8/8/8/8/8/3k4 w - - 0 1",
                                          "8/8/1P2K3/8/2n5/1q6/8/5k2 b - - 0 1",
                                          "4k3/1P6/8/8/8/8/K7/8 w - - 0 1",
                                          "8/P1k5/K7/8/8/8/8/8 w - - 0 1",
                                          "K1k5/8/P7/8/8/8/8/8 w - - 0 1",
                                          "8/k1P5/8/1K6/8/8/8/8 w - - 0 1",
                                          "8/8/2k5/5q2/5n2/8/5K2/8 b - - 0 1"};
