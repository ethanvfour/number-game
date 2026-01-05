#ifndef BOARD_H
#define BOARD_H

#include <utility>
#include <array>
#include "Tile.h"

constexpr int BOARD_SIZE = 4;

namespace UserInput
{
    enum class Input
    {
        UP,
        LEFT,
        DOWN,
        RIGHT,
        QUIT,
        NULL_INPUT,
    };

    Input getUserInput();
};

class Board
{
    std::pair<int, int> emptySpace{};
    std::array<std::array<Tile, 4>, 4> board{};

    void intializeBoard();

    void printBoard() const;

    bool hasWon() const;

    void handleBoardMove(UserInput::Input move);

public:
    Board();

    void run();
};

#endif