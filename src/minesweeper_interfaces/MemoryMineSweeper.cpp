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

//Constructors
MemoryMineSweeper::MemoryMineSweeper(const FixedTable<bool> &mineDistribution)
    : mineDistribution(mineDistribution), gameState(mineDistribution.GetNumberOfRows(), mineDistribution.GetNumberOfColumns())
{
    this->InitGameState();
}

MemoryMineSweeper::MemoryMineSweeper(uint16 nRows, uint16 nCols, uint16 nMines)
    : mineDistribution(nRows, nCols), gameState(nRows, nCols)
{
    this->InitGameState();

    for (uint32 row = 0; row < this->mineDistribution.GetNumberOfRows(); row++)
    {
        for (uint32 col = 0; col < this->mineDistribution.GetNumberOfColumns(); col++)
        {
            this->mineDistribution(row, col) = false;
        }
    }

    Math::MinStdRand randomNumberGenerator(static_cast<uint32>(DateTime::Now().Time().NanosecondsSinceStartOfDay()));
    Math::UniformUnsignedDistribution rowDistribution(randomNumberGenerator, 0_u16, uint16(nRows - 1));
    Math::UniformUnsignedDistribution colDistribution(randomNumberGenerator, 0_u16, uint16(nCols - 1));
    while(nMines)
    {
        uint16 row = rowDistribution.Next();
        uint16 col = colDistribution.Next();

        if(!this->mineDistribution(row, col))
        {
            this->mineDistribution(row, col) = true;
            nMines--;
        }
    }
}

//Public methods
void MemoryMineSweeper::DoMove(const GameMove &move)
{
    auto& fieldState = this->gameState(move.row, move.column);
    ASSERT_EQUALS(BoxState::Unrevealed, fieldState);

    if(move.type == GameMoveType::Reveal)
    {
        fieldState = this->ComputeRealBoxState(move.row, move.column);
        if(fieldState == BoxState::Empty)
            this->AutoRevealNeighborFields(move.row, move.column);
    }
    else
        fieldState = BoxState::Defused;
}

BoxState MemoryMineSweeper::QueryBoxState(uint16 row, uint16 col) const
{
    return this->gameState(row, col);
}

uint16 MemoryMineSweeper::QueryNumberOfColumns() const
{
    return this->mineDistribution.GetNumberOfColumns();
}

uint16 MemoryMineSweeper::QueryNumberOfRows() const
{
    return this->mineDistribution.GetNumberOfRows();
}

//Private methods
void MemoryMineSweeper::AutoRevealNeighborFields(uint16 row, uint16 column)
{
    DynamicArray<Field> neighbors = this->CollectSurroundingBoxes(row, column);

    for(const Field& neighbor : neighbors)
    {
        if(this->gameState(neighbor.row, neighbor.column) == BoxState::Unrevealed)
        {
            GameMove gameMove;
            gameMove.column = neighbor.column;
            gameMove.row = neighbor.row;
            gameMove.type = GameMoveType::Reveal;
            this->DoMove(gameMove);
        }
    }
}

DynamicArray<MemoryMineSweeper::Field> MemoryMineSweeper::CollectSurroundingBoxes(uint16 row, uint16 column) const
{
    DynamicArray<MemoryMineSweeper::Field> fields;

    for(int32 y = row - 1; y <= row + 1; y++)
    {
        for(int32 x = column - 1; x <= column + 1; x++)
        {
            if((y >= 0) and (y < this->QueryNumberOfRows()) and (x >= 0) and (x < this->QueryNumberOfColumns()))
            {
                Field field;
                field.column = x;
                field.row = y;
                field.boxState = this->gameState(y, x);
                field.isMine = this->mineDistribution(y, x);
                fields.Push(field);
            }
        }
    }

    return fields;
}

uint8 MemoryMineSweeper::ComputeNumberOfNeighborMines(uint16 row, uint16 column) const
{
    DynamicArray<MemoryMineSweeper::Field> neighborFields = this->CollectSurroundingBoxes(row, column);
    uint8 nMines = 0;
    for(const auto& neighborField : neighborFields)
    {
        if(neighborField.isMine)
            nMines++;
    }
    return nMines;
}

BoxState MemoryMineSweeper::ComputeRealBoxState(uint16 row, uint16 column) const
{
    const auto& fieldState = this->gameState(row, column);
    if(fieldState == BoxState::Unrevealed)
    {
        if(this->mineDistribution(row, column))
            return BoxState::Mine;

        uint8 nMines = this->ComputeNumberOfNeighborMines(row, column);
        return this->GetBoxStateForNumberOfSurroundingMines(nMines);

    }
    return fieldState;
}

void MemoryMineSweeper::InitGameState()
{
    for (uint32 row = 0; row < this->gameState.GetNumberOfRows(); row++)
    {
        for (uint32 col = 0; col < this->gameState.GetNumberOfColumns(); col++)
        {
            this->gameState(row, col) = BoxState::Unrevealed;
        }
    }
}

BoxState MemoryMineSweeper::GetBoxStateForNumberOfSurroundingMines(uint8 nMines) const
{
    switch(nMines)
    {
        case 0:
            return BoxState::Empty;
        case 1:
            return BoxState::NearbyMines1;
        case 2:
            return BoxState::NearbyMines2;
        case 3:
            return BoxState::NearbyMines3;
        case 4:
            return BoxState::NearbyMines4;
        default:
            NOT_IMPLEMENTED_ERROR;
    }
}