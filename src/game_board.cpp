// Game of 8
// Copyright (C) 2018 Yurii Khomiak 
// Yurii Khomiak licenses this file to you under the MIT license. 
// See the LICENSE file in the project root for more information.

#include "game_board.h"

#include <iostream>
#include <array>
#include <list>
#include <memory>

GameBoard::GameBoard(std::array< std::array< char, 3 >, 3 > board)
{
    for (int i = 0; i < size_; i++)
    {
        for (int j = 0; j < size_; j++)
        {
            board_[i][j] = board.at(i).at(j);

            if (board_[i][j] == ' ')
            {
                row_blank_ = i;
                col_blank_ = j;
            }
        }
    }

    is_init_ = true;
}

GameBoard GameBoard::move(Direction direction) const
{
    GameBoard result;

    switch (direction)
    {
    case Direction::DOWN:
        move_down(result);
        break;

    case Direction::LEFT:
        move_left(result);
        break;

    case Direction::UP:
        move_up(result);
        break;

    case Direction::RIGHT:
        move_right(result);
        break;
    }

    return result;
}

void GameBoard::move_down(GameBoard &board) const
{
    if (row_blank_ == (size_ - 1))
    {
        return;
    }

    board = *this;

    board.board_[row_blank_][col_blank_] = board_[row_blank_ + 1][col_blank_];
    board.board_[row_blank_ + 1][col_blank_] = ' ';

    board.parent = std::make_shared<GameBoard>(*this);

    ++board.row_blank_;
}

void GameBoard::move_left(GameBoard &board) const
{
    if (col_blank_ == 0)
    {
        return;
    }

    board = *this;

    board.board_[row_blank_][col_blank_] = board_[row_blank_][col_blank_ - 1];
    board.board_[row_blank_][col_blank_ - 1] = ' ';

    board.parent = std::make_shared<GameBoard>(*this);

    --board.col_blank_;
}

void GameBoard::move_up(GameBoard &board) const
{
    if (row_blank_ == 0)
    {
        return;
    }

    board = *this;

    board.board_[row_blank_][col_blank_] = board_[row_blank_ - 1][col_blank_];
    board.board_[row_blank_ - 1][col_blank_] = ' ';

    board.parent = std::make_shared<GameBoard>(*this);

    --board.row_blank_;
}

void GameBoard::move_right(GameBoard &board) const
{
    if (col_blank_ == (size_ - 1))
    {
        return;
    }

    board = *this;

    board.board_[row_blank_][col_blank_] = board_[row_blank_][col_blank_ + 1];
    board.board_[row_blank_][col_blank_ + 1] = ' ';

    board.parent = std::make_shared<GameBoard>(*this);

    ++board.col_blank_;
}

void GameBoard::show_path() const
{
    std::list<GameBoard> path;
    auto trace = std::make_shared<GameBoard>(*this);

    while (trace != nullptr)
    {
        path.push_back(*trace);
        trace = trace->parent;
    }

    auto iter = path.rbegin();
    while (iter != path.rend())
    {
        std::cout << *(iter++);
    }
}

bool GameBoard::operator==(const GameBoard& board) const
{
    for (int i = 0; i < size_; i++)
    {
        for (int j = 0; j < size_; j++)
        {
            if (board_[i][j] != board.board_[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

std::ostream& operator<<(std::ostream &stream, const GameBoard &board)
{
    stream << std::endl;

    for (int i = 0; i < board.size_; i++)
    {
        stream << "+---+---+---+\n";
        for (int j = 0; j < board.size_; j++)
        {
            stream << "| " << board.board_[i][j] << ' ';
        }
        stream << "|\n";
    }
    stream << "+---+---+---+\n";

    stream << std::endl;
    return stream;
}
