/*
* Copyright (c) 2021 Amir Czwink (amir130@hotmail.de)
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
#include <StdXX.hpp>
//Local
#include "BoxState.hpp"
#include "PlayingState.hpp"

using namespace StdXX;

struct IndexedField
{
    uint16 column;
    uint16 row;
    BoxState boxState;
};

class BoardState
{
public:
    //Constructor
    inline BoardState(FixedTable<BoxState>&& fields) : fields(Move(fields))
    {
    }

    //Properties
    inline uint16 NumberOfColumns() const
    {
        return this->fields.GetNumberOfColumns();
    }

    inline uint16 NumberOfRows() const
    {
        return this->fields.GetNumberOfRows();
    }

    //Methods
    DynamicArray<IndexedField> CollectSurroundingBoxes(uint16 row, uint16 column) const;
    PlayingState ComputePlayingState() const;
    String ToString() const;

    //Inline
    inline BoxState GetState(uint16 row, uint16 column) const
    {
        return this->fields(row, column);
    }

private:
    //Members
    FixedTable<BoxState> fields;
};