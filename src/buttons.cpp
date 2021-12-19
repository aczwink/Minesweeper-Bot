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
//Main Header
#include "buttons.h"
//Local
#include "CLog.h"
#include "MainWindow.hpp"
#include "MineSweeperBot.h"
#include "resource.h"
//Namespaces
using namespace SJCLib;

//CButtonSolve Message-callbacks
void CButtonSolve::OnClick()
{
	MineSweeperInterface &msi = MineSweeperInterface::GetInstance();
	MineSweeperBot &bot = MineSweeperBot::GetInstance();

	if(!msi.IsInitiated())
	{
		if(!msi.Init())
		{
			this->GetParent()->MessageBoxA("MineSweeper wasn't found.", "Error", MB_ICONERROR);
			return;
		}
	}
	LOGINFO("Rows: " + CString(msi.GetNoOfRows()) + " Columns: " + CString(msi.GetNoOfColumns()));
	if(!bot.IsInitiated())
		bot.Init();
	this->GetParent()->PostMessageA(WM_USER_SOLVE, 0, 0);
}

//CButtonStep Message-callbacks
void CButtonStep::OnClick()
{
	MineSweeperInterface &msi = MineSweeperInterface::GetInstance();
	MineSweeperBot &bot = MineSweeperBot::GetInstance();

	if(!msi.IsInitiated())
	{
		if(!msi.Init())
		{
			this->GetParent()->MessageBoxA("MineSweeper wasn't found.", "Error", MB_ICONERROR);
			return;
		}
		LOGINFO("Rows: " + CString(msi.GetNoOfRows()) + " Columns: " + CString(msi.GetNoOfColumns()));
	}
	else
	{
		if(!msi.IsMineSweeperStillActive())
		{
			this->GetParent()->MessageBoxA("It seems that MineSweeper was closed.", "Error", MB_ICONERROR);
			return;
		}
	}
	if(!bot.IsInitiated())
		bot.Init();
	bot.Step();
	bot.ClearFields();
}

//CButtonClearLog Message-callbacks
void CButtonClearLog::OnClick()
{
	((CMainWindow *)this->GetParent())->listLog.Clear();
}