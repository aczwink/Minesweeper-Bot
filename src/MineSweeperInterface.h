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
//SJC Libs
#include <SJCWinLib.h>
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;
//Definitions
#define MINESWEEPER_BOTTOMSPACING MINESWEEPER_RIGHTSPACING
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
#define MINESWEEPER_BOXCHECKSUMS_UNREVEALED 0x23F5E
#define MINESWEEPER_BOXCHECKSUMS_WRONGMINE 0x17ACF
#define MINESWEEPER_BOXSIZE 16
#define MINESWEEPER_LEFTSPACING 12
#define MINESWEEPER_MINESWEEPERFIELDNAME "MineSweeper"
#define MINESWEEPER_RIGHTSPACING 8
#define MINESWEEPER_TOPSPACING 55
#define MINESWEEPER_WINDOWNAME "Minesweeper"

enum EBoxState
{
	BOXSTATE_UNKNOWN, //this should never appear
	BOXSTATE_NOTEXISTENT, //-1 -1 for instance does not exist //check usage
	BOXSTATE_UNREVEALED,
	BOXSTATE_EMPTY,
	BOXSTATE_DEFUSED,
	BOXSTATE_MINE, //if the bot fails
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
	CPointer<CDeviceContext> dc;
	CWindow *pMSWnd;
	CRect rcClient;
	CRect rcWindow;
	int32 resolutionX;
	int32 resolutionY;
	//Functions
	uint32 GetBoxPixelChecksum(uint16 column, uint16 row);
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
	void MoveMouseOnField(int32 column, int32 row);
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

#define MOUSE_MAXPOS 65535

class MineSweeperInterface
{
private:
	//vars
	//functions
	void MoveMouse(ushort x, ushort y);
	//constructor
	MineSweeperInterface();
public:
	//destructor
	~MineSweeperInterface();
	//functions
//	void markBox(ushort column, ushort row);
};*/
