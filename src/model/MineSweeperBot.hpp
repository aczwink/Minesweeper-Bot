/*
* Copyright (c) 2018,2021 Amir Czwink (amir130@hotmail.de)
*
* This file is part of Minesweeper-Bot.
*
* Minesweeper-Bot is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Minesweeper-Bot is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Minesweeper-Bot.  If not, see <http://www.gnu.org/licenses/>.
*/
//Local
#include "MineSweeperInterface.hpp"
#include "MovesLogger.hpp"

class MineSweeperBot
{
public:
    //Constructor
    inline MineSweeperBot(MineSweeperInterface& mineSweeperInterface, MovesLogger& logger)
        : mineSweeperInterface(mineSweeperInterface), logger(logger)
    {
        this->guess = false;
    }

    //Methods
    void Step();

    //Inline
    inline void EnableGuessing(bool guess)
    {
        this->guess = guess;
    }

private:
    //Members
    bool guess;
    MineSweeperInterface& mineSweeperInterface;
    MovesLogger& logger;

    //Methods
    void DoMove(const BoardState& boardState);
};