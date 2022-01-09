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
#pragma once
#include "BoardState.hpp"
#include "GameMove.hpp"

class MineSweeperInterface
{
public:
    //Destructor
    virtual ~MineSweeperInterface(){}

    //Abstract
    virtual void DoMove(const GameMove& move) = 0;
    virtual BoxState QueryBoxState(uint16 row, uint16 col) const = 0;
    virtual uint16 QueryNumberOfColumns() const = 0;
    virtual uint16 QueryNumberOfRows() const = 0;

    //Inline
    inline BoardState QueryState() const
    {
        FixedTable<BoxState> fields(this->QueryNumberOfRows(), this->QueryNumberOfColumns());
        for (uint16 row = 0; row < this->QueryNumberOfRows(); row++)
        {
            for (uint16 col = 0; col < this->QueryNumberOfColumns(); col++)
                fields(row, col) = this->QueryBoxState(row, col);
        }
        return fields;
    }
};