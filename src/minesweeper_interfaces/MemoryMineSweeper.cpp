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
//Class header
#include "MemoryMineSweeper.hpp"

//Constructor
MemoryMineSweeper::MemoryMineSweeper(Log &log, uint16 nRows, uint16 nCols, uint16 nMines)
    : MineSweeperInterface(log),
    gameState(nRows, nCols)
{
    //clear fields
    for (uint32 row = 0; row < this->gameState.GetNumberOfRows(); row++)
    {
        for (uint32 col = 0; col < this->gameState.GetNumberOfColumns(); col++)
        {
            auto& field = this->gameState(row, col);

            field.state = BoxState::Unrevealed;
            field.isMine = false;
        }
    }

    Math::MinStdRand randomNumberGenerator;
    Math::UniformUnsignedDistribution rowDistribution(randomNumberGenerator, 0_u16, uint16(nRows - 1));
    Math::UniformUnsignedDistribution colDistribution(randomNumberGenerator, 0_u16, uint16(nCols - 1));
    while(nMines)
    {
        uint16 row = rowDistribution.Next();
        uint16 col = colDistribution.Next();

        if(!this->gameState(row, col).isMine)
        {
            this->gameState(row, col).isMine = true;
            nMines--;
        }
    }
}

//Public methods
void MemoryMineSweeper::Defuse(uint32 column, uint32 row)
{
    NOT_IMPLEMENTED_ERROR; //TODO: implement me
}

BoxState MemoryMineSweeper::GetBoxState(uint16 row, uint16 col) const
{
    return this->gameState(row, col).state;
}

uint16 MemoryMineSweeper::GetNumberOfColumns() const
{
    return this->gameState.GetNumberOfColumns();
}

uint16 MemoryMineSweeper::GetNumberOfRows() const
{
    return this->gameState.GetNumberOfRows();
}

void MemoryMineSweeper::Reveal(uint16 column, uint16 row)
{
    auto& field = this->gameState(row, column);
    ASSERT_EQUALS(BoxState::Unrevealed, field.state);
    field.state = this->ComputeRealBoxState(column, row);
}

//Private methods
DynamicArray<MemoryMineSweeper::Field> MemoryMineSweeper::CollectSurroundingBoxes(uint16 column, uint16 row) const
{
    DynamicArray<MemoryMineSweeper::Field> fields;

    for(int32 y = row - 1; y <= row + 1; y++)
    {
        for(int32 x = column - 1; x <= column + 1; x++)
        {
            if((y >= 0) and (y < this->GetNumberOfRows()) and (x >= 0) and (x < this->GetNumberOfColumns()))
                fields.Push(this->gameState(y, x));
        }
    }

    return fields;
}

BoxState MemoryMineSweeper::ComputeRealBoxState(uint16 column, uint16 row) const
{
    const auto& field = this->gameState(row, column);
    if(field.state == BoxState::Unrevealed)
    {
        if(field.isMine)
            return BoxState::Mine;

        DynamicArray<MemoryMineSweeper::Field> neighborFields = this->CollectSurroundingBoxes(column, row);
        uint8 nMines = 0;
        for(const auto& neighborField : neighborFields)
        {
            if(neighborField.isMine)
                nMines++;
        }
        return this->GetBoxStateForNumberOfSurroundingMines(nMines);

    }
    return field.state;
}

BoxState MemoryMineSweeper::GetBoxStateForNumberOfSurroundingMines(uint8 nMines) const
{
    switch(nMines)
    {
        case 2:
            return BoxState::NearbyMines2;
        case 4:
            return BoxState::NearbyMines4;
        default:
            NOT_IMPLEMENTED_ERROR;
    }
}
