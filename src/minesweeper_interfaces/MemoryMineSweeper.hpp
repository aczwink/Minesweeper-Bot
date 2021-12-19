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
//Local
#include "../MineSweeperInterface.hpp"


class MemoryMineSweeper : public MineSweeperInterface
{
    struct Field
    {
        BoxState state;
        bool isMine;
    };
public:
    //Constructors
    MemoryMineSweeper(Log &log, uint16 nRows, uint16 nCols, uint16 nMines);

    //Methods
    void Defuse(uint32 column, uint32 row) override;
    BoxState GetBoxState(uint16 row, uint16 col) const override;
    uint16 GetNumberOfColumns() const override;
    uint16 GetNumberOfRows() const override;
    void Reveal(uint16 column, uint16 row) override;

private:
    //Members
    FixedTable<Field> gameState;

    //Methods
    DynamicArray<Field> CollectSurroundingBoxes(uint16 column, uint16 row) const;
    BoxState ComputeRealBoxState(uint16 column, uint16 row) const;
    BoxState GetBoxStateForNumberOfSurroundingMines(uint8 nMines) const;
};