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
//Class header
#include "BoardState.hpp"

//Public methods
DynamicArray<IndexedField> BoardState::CollectSurroundingBoxes(uint16 row, uint16 column) const
{
    DynamicArray<IndexedField> result;
    result.EnsureCapacity(8); //max number of surrounding boxes is 8

    for(int32 y = row - 1; y <= row + 1; y++)
    {
        for(int32 x = column - 1; x <= column + 1; x++)
        {
            if (y == row && x == column)
                continue; //skip the field itself

            if((y >= 0) and (y < this->NumberOfRows()) and (x >= 0) and (x < this->NumberOfColumns()))
            {
                IndexedField field;
                field.column = x;
                field.row = y;
                field.boxState = this->GetState(y, x);
                result.Push(field);
            }
        }
    }

    return result;
}

PlayingState BoardState::ComputePlayingState() const
{
    bool active = false;
    for (uint32 row = 0; row < this->fields.GetNumberOfRows(); row++)
    {
        for (uint32 col = 0; col < this->fields.GetNumberOfColumns(); col++)
        {
            auto field = this->fields(row, col);
            if (field == BoxState::Mine)
            {
                return PlayingState::Lost;
            }
            else if(field == BoxState::Unrevealed)
                active = true;
        }
    }

    return active ? PlayingState::Active : PlayingState::Won;
}

String BoardState::ToString() const
{
    String fieldString;

    for (uint32 row = 0; row < this->fields.GetNumberOfRows(); row++)
    {
        fieldString += u8"|";
        for (uint32 col = 0; col < this->fields.GetNumberOfColumns(); col++)
        {
            switch (this->fields(row, col))
            {
                case BoxState::Defused:
                    fieldString += u8"!";
                    break;
                case BoxState::Empty:
                    fieldString += u8" ";
                    break;
                case BoxState::Mine:
                    fieldString += u8"X";
                    break;
                case BoxState::NearbyMines1:
                    fieldString += u8"1";
                    break;
                case BoxState::NearbyMines2:
                    fieldString += u8"2";
                    break;
                case BoxState::NearbyMines3:
                    fieldString += u8"3";
                    break;
                case BoxState::NearbyMines4:
                    fieldString += u8"4";
                    break;
                case BoxState::Unrevealed:
                    fieldString += u8"?";
                    break;
                    /*
                    case BOXSTATE_WRONGMINE:
                        CLog::WriteString("#");
                        break;
                    case BOXSTATE_5NEARBYBOMBS:
                        CLog::WriteString("5");
                        break;
                    case BOXSTATE_6NEARBYBOMBS:
                        CLog::WriteString("6");
                        break;
                    case BOXSTATE_7NEARBYBOMBS:
                        CLog::WriteString("7");
                        break;
                    case BOXSTATE_8NEARBYBOMBS:
                        CLog::WriteString("8");
                        break;*/
            }
            fieldString += u8"|";
        }
        fieldString += u8"\r\n";
    }

    return fieldString;
}