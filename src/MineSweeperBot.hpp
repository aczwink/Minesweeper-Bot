/*
* Copyright (c) 2018 Amir Czwink (amir130@hotmail.de)
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

class MineSweeperBot
{
public:
	//Constructor
	MineSweeperBot(UniquePointer<MineSweeperInterface> &&msInterface, Log &log);

	//Methods
	bool CanContinue();
	void Step();

private:
	//Members
	uint16 maxMoves;
	UniquePointer<MineSweeperInterface> msInterface;
	Log &log;
};
/*
//Local
#include "MineSweeperInterface.hpp"

//Structs
struct SField
{
	int16 column;
	int16 row;
	EBoxState state;
};

class MineSweeperBot
{
private:
	//Variables
	bool isInitiated;
	bool guess;
	uint16 rows;
	uint16 columns;
	EBoxState **ppFields;
	//Functions
	bool DoMove();
	void EnterName();
	void GetSurroundingBoxes(uint16 column, uint16 row, CArray<SField> &surroundingBoxes);
	bool Guess();
	void UpdateFields();
public:
	//Constructor
	MineSweeperBot();
	//Destructor
	~MineSweeperBot();
	//Functions
	void ClearFields();
	static MineSweeperBot &GetInstance();
	void Init();
	bool IsInitiated();
	void Release();
	void SetGuess(bool guess);
};

/*#pragma once
//global
//#include <conio.h>
//local
#include "MineSweeperInterface.h"

class MineSweeperBot
{
private:
//constructor
	MineSweeperBot();
public:
	//destructor
	~MineSweeperBot();
};*/