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
//Local
#include "Log.hpp"

enum class BoxState
{
	Unrevealed,
	Defused,
	Mine, //a revealed mine, i.e. when game was lost
	NearbyMines2,
	NearbyMines4
};

class MineSweeperInterface
{
public:
	//Constructor
	inline MineSweeperInterface(Log &log) : log(log)
	{
	}

	//Destructor
	virtual ~MineSweeperInterface(){}

	//Abstract
	virtual void Defuse(uint32 column, uint32 row) = 0;
	virtual BoxState GetBoxState(uint16 row, uint16 col) const = 0;
	virtual uint16 GetNumberOfColumns() const = 0;
	virtual uint16 GetNumberOfRows() const = 0;
	virtual void Reveal(uint16 column, uint16 row) = 0;

protected:
	//Members
	Log &log;
};