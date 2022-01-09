/*
 * Copyright (c) 2021 Amir Czwink (amir130@hotmail.de)
 *
 * This file is part of ACBackup.
 *
 * ACBackup is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ACBackup is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ACBackup.  If not, see <http://www.gnu.org/licenses/>.
 */
//Local
#include "../src/model/BoardState.hpp"
#include "../src/minesweeper_interfaces/MemoryMineSweeper.hpp"

class BoardBuilder
{
public:
    //Constructor
    inline BoardBuilder(uint16 nRows, uint16 nCols) : mines(nRows, nCols)
    {
        for (uint16 row = 0; row < nRows; row++)
        {
            for (uint16 col = 0; col < nCols; col++)
            {
                this->mines(row, col) = false;
            }
        }
    }

    //Properties
    inline MineSweeperInterface& Interface()
    {
        if(this->memoryMineSweeper.IsNull())
            this->memoryMineSweeper = new MemoryMineSweeper(this->mines);
        return *this->memoryMineSweeper;
    }

    //Inline
    inline void SetMine(uint16 row, uint16 col)
    {
        this->mines(row, col) = true;
    }

    inline void SetRevealed(uint16 row, uint16 col)
    {
        GameMove gameMove;
        gameMove.type = GameMoveType::Reveal;
        gameMove.row = row;
        gameMove.column = col;

        this->Interface().DoMove(gameMove);
    }

private:
    //Members
    FixedTable<bool> mines;
    UniquePointer<MemoryMineSweeper> memoryMineSweeper;
};