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
//Global
#include <Windows.h>
//Local
#include "MineSweeperInterface.hpp"

class MineSweeperXPInterface : public MineSweeperInterface
{
public:
	//Constructor
	inline MineSweeperXPInterface(Log &log) : MineSweeperInterface(log),
		hMSWnd(nullptr)
	{
		this->AssertConnected();
		this->resolutionX = GetSystemMetrics(SM_CXSCREEN);
		this->resolutionY = GetSystemMetrics(SM_CYSCREEN);
	}

	//Destructor
	~MineSweeperXPInterface();

	//Methods
	void Defuse(uint32 column, uint32 row) override;
	BoxState GetBoxState(uint16 row, uint16 col) const override;
	uint16 GetNumberOfColumns() const override;
	uint16 GetNumberOfRows() const override;
	void Reveal(uint32 column, uint32 row) override;

private:
	//Members
	HWND hMSWnd;
	RECT rcClient;
	HDC hDC;
	int32 resolutionX;
	int32 resolutionY;

	//Methods
	bool Connect();
	uint32 GetBoxPixelChecksum(uint16 column, uint16 row) const;
	void MoveMouseOverField(uint32 column, uint32 row);
	void MoveMouseTo(uint16 x, uint16 y);

	//Inline
	inline void AssertConnected()
	{
		ASSERT(this->Connect(), u8"Couldn't connect to Minesweeper XP window");
	}
};
/*
//SJC Libs
#include <SJCWinLib.h>
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;
//Definitions
#define MINESWEEPER_BOXCHECKSUMS_1NEARBYBOMB 0x1F698
#define MINESWEEPER_BOXCHECKSUMS_2NEARBYBOMBS 0x1B700
#define MINESWEEPER_BOXCHECKSUMS_3NEARBYBOMBS 0x1DB02
#define MINESWEEPER_BOXCHECKSUMS_4NEARBYBOMBS 0x1C6C0
#define MINESWEEPER_BOXCHECKSUMS_5NEARBYBOMBS 0x1AE40
#define MINESWEEPER_BOXCHECKSUMS_6NEARBYBOMBS 0x1CEC0
#define MINESWEEPER_BOXCHECKSUMS_7NEARBYBOMBS 0x1C5C0
#define MINESWEEPER_BOXCHECKSUMS_8NEARBYBOMBS 0x1EFC0
#define MINESWEEPER_BOXCHECKSUMS_ACTIVEMINE 0xC9E4
#define MINESWEEPER_BOXCHECKSUMS_DEFUSED 0x1F88D
#define MINESWEEPER_BOXCHECKSUMS_EMPTY 0x228C0
#define MINESWEEPER_BOXCHECKSUMS_MINE 0x17E74
#define MINESWEEPER_BOXCHECKSUMS_WRONGMINE 0x17ACF
#define MINESWEEPER_MINESWEEPERFIELDNAME "MineSweeper"

enum EBoxState
{
	BOXSTATE_NOTEXISTENT, //-1 -1 for instance does not exist //check usage
	BOXSTATE_EMPTY,
	BOXSTATE_DEFUSED,
	BOXSTATE_WRONGMINE, //should never appear
	BOXSTATE_1NEARBYBOMB,
	BOXSTATE_2NEARBYBOMBS,
	BOXSTATE_3NEARBYBOMBS,
	BOXSTATE_4NEARBYBOMBS,
	BOXSTATE_5NEARBYBOMBS,
	BOXSTATE_6NEARBYBOMBS,
	BOXSTATE_7NEARBYBOMBS,
	BOXSTATE_8NEARBYBOMBS
};

class MineSweeperInterface
{
private:
	//Variables
	CRect rcWindow;
public:
	//Constructor
	MineSweeperInterface();
	//Destructor
	~MineSweeperInterface();
	//Functions
	void Defuse(int32 column, int32 row);
	EBoxState GetBoxState(uint16 column, uint16 row);
	static MineSweeperInterface &GetInstance();
	uint32 GetNoOfColumns();
	uint32 GetNoOfRows();
	CDialog *GetWonDialog();
	bool Init();
	bool IsInitiated();
	bool IsMineSweeperStillActive();
	void Release();
	void Reveal(int32 column, int32 row);
};

/*#pragma once
//global
//SJCLib
#include <SJCLibWindows.h>
//local
#include "log.h"

using namespace SJCLibWindows;
//definitions
class MineSweeperInterface
{
private:
	//constructor
	MineSweeperInterface();
public:
	//destructor
	~MineSweeperInterface();
	//functions
//	void markBox(ushort column, ushort row);
};*/