#include "Board.h"
#include <algorithm>
#include <random>
#include <vector>
#include <iostream>
#include <limits>
#include <iomanip>

// USERINPUT IMP

UserInput::Input UserInput::getUserInput()
{
    char ch{};
    // assuming message was already outputted

    std::cin >> ch;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    UserInput::Input returner{UserInput::Input::NULL_INPUT};

    switch (ch)
    {
    case 'w':
        returner = Input::UP;
        break;
    case 'a':
        returner = Input::LEFT;
        break;
    case 's':
        returner = Input::DOWN;
        break;
    case 'd':
        returner = Input::RIGHT;
        break;
    case 'q':
        returner = Input::QUIT;
        break;
    default:
        returner = Input::NULL_INPUT;
        break;
    }

    return returner;
}

// BOARD IMP

Board::Board() : emptySpace{0, 0}, board{}
{
    intializeBoard();
}

void Board::intializeBoard()
{
    std::vector<int> nums((BOARD_SIZE * BOARD_SIZE) - 1);

    for (int i{1}; i < BOARD_SIZE * BOARD_SIZE; i++)
        nums[i - 1] = i;

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(nums.begin(), nums.end(), g);

    for (int i{}, index{}; i < BOARD_SIZE; i++)
    {
        for (int j{}; j < BOARD_SIZE; j++)
        {
            if (i == 0 && j == 0)
                board[i][j].setNum(0);
            else
                board[i][j].setNum(nums[index++]);
        }
    }
}

void Board::printBoard() const
{
    std::cout << std::left;

    for (int i{}, index{1}; i < BOARD_SIZE; i++)
    {
        for (int j{}; j < BOARD_SIZE; j++)
        {
            std::cout
                << (board[i][j].getNum() == index++ ? "\033[31m" : "")
                << std::setw(5)
                << board[i][j].getNum()
                << "\033[0m ";
        }
        std::cout << "\n";
    }
}

bool Board::hasWon() const
{
    for (int i{}, index{1}; i < BOARD_SIZE; i++)
    {
        for (int j{}; j < BOARD_SIZE; j++)
        {
            if (int hello = board[i][j].getNum();
                hello != index++)
                return false;
        }
    }
    return true;
}

void Board::handleBoardMove(UserInput::Input move)
{
    using uInput = UserInput::Input;

    std::pair<int, int> toSwitchTo{};
    auto [currY, currX] = emptySpace;

    switch (move)
    {
    case uInput::UP:
        // handle move up
        toSwitchTo = {currY + 1, currX};
        break;
    case uInput::DOWN:
        // handle move down
        toSwitchTo = {currY - 1, currX};
        break;
    case uInput::LEFT:
        // handle move left
        toSwitchTo = {currY, currX + 1};
        break;
    case uInput::RIGHT:
        // handle move right
        toSwitchTo = {currY, currX - 1};
        break;
    default:
        // do nothing for QUIT and NULL_INPUT
        throw std::runtime_error("Cannot move on quit and null!\n");
    }

    auto isInRange = [&toSwitchTo]() -> bool
    {
        auto [y, x] = toSwitchTo;
        return (0 <= y && y < BOARD_SIZE) && (0 <= x && x < BOARD_SIZE);
    };

    if (isInRange())
    {
        auto [newY, newX] = toSwitchTo;
        std::swap(board[currY][currX], board[newY][newX]);
        emptySpace = toSwitchTo;
    }
}

void Board::run()
{
    using uInput = UserInput::Input;
    bool quit{false};

    while (!hasWon() && !quit)
    {
        printBoard();

        uInput curr{uInput::NULL_INPUT};
        while (curr == uInput::NULL_INPUT)
        {
            std::cout << "Input (w/a/s/d/q): ";
            curr = UserInput::getUserInput();
            if (curr == uInput::NULL_INPUT)
            {
                std::cout << "Bad Input!\n";
            }
        }

        if (curr == uInput::QUIT)
        {
            quit = true;
            continue;
        }

        handleBoardMove(curr);
    }

    if (!quit)
    {
        std::cout << "You've won!\n";
    }
}