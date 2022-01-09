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
//Local
#include "../model/MineSweeperInterface.hpp"

class MemoryMineSweeper : public MineSweeperInterface
{
    struct Field : public IndexedField
    {
        bool isMine;
    };
public:
    //Constructors
    MemoryMineSweeper(const FixedTable<bool>& mineDistribution);
    MemoryMineSweeper(uint16 nRows, uint16 nCols, uint16 nMines);

    //Methods
    void DoMove(const GameMove &move) override;
    BoxState QueryBoxState(uint16 row, uint16 col) const override;
    uint16 QueryNumberOfColumns() const override;
    uint16 QueryNumberOfRows() const override;

private:
    //Members
    FixedTable<bool> mineDistribution;
    FixedTable<BoxState> gameState;

    //Methods
    void AutoRevealNeighborFields(uint16 row, uint16 column);
    DynamicArray<Field> CollectSurroundingBoxes(uint16 row, uint16 column) const;
    uint8 ComputeNumberOfNeighborMines(uint16 row, uint16 column) const;
    BoxState ComputeRealBoxState(uint16 row, uint16 column) const;
    BoxState GetBoxStateForNumberOfSurroundingMines(uint8 nMines) const;
    void InitGameState();
};