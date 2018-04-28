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
//Class header
#include "MainWindow.hpp"

//Constructor
MainWindow::MainWindow(EventQueue &eventQueue) : MainAppWindow(eventQueue)
{
	this->SetTitle(u8"Minesweeper Bot");
}

/*
//Local
#include "CLog.h"
#include "MineSweeperBot.h"
#include "resource.h"

//Message-callbacks
bool MainWindow::OnCreate()
{
	CFont font;

	font.CreateSystemFont(DEFAULT_GUI_FONT);

	this->listLog.Create(WS_VSCROLL | WS_BORDER, 0, 0, 0, 0, 0, *this);
	this->listLog.SetFont(font);

	this->guessCheckBox.Create("Guess", 0, 0, 0, 0, 0, *this);
	this->guessCheckBox.SetFont(font);

	this->buttonSolve.Create("Solve", 0, 0, 0, 0, 0, *this);
	this->buttonSolve.SetFont(font);

	this->buttonStep.Create("Step", 0, 0, 0, 0, 0, *this);
	this->buttonStep.SetFont(font);

	this->buttonClearLog.Create("Clear log", 0, 0, 0, 0, 0, *this);
	this->buttonClearLog.SetFont(font);

	this->PostMessageA(WM_USER_CREATED, 0, 0);

	return true;
}

void MainWindow::OnDestroy()
{
	MineSweeperBot &bot = MineSweeperBot::GetInstance();

	LOGINFO("Program end");
	bot.Release();
	CLog::Close();
	PostQuitMessage(EXIT_SUCCESS);
}

void MainWindow::OnSize(WPARAM resizingType, uint32 newWidth, uint32 newHeight)
{
	CRect rcClient;
	CRect rcList;
	CRect rcCheckboxGuess;
	CRect rcButtonSolve;
	CRect rcButtonStep;
	CRect rcButtonClearLog;

	this->GetClientRect(&rcClient);

	rcButtonSolve.left = 5;
	rcButtonSolve.top = rcClient.bottom - 5 - 23;
	rcButtonSolve.right = 75;
	rcButtonSolve.bottom = rcButtonSolve.top + 23;

	rcButtonStep.left = rcButtonSolve.right + 6;
	rcButtonStep.top = rcButtonSolve.top;
	rcButtonStep.right = rcButtonStep.left + rcButtonSolve.right;
	rcButtonStep.bottom = rcButtonSolve.bottom;

	rcButtonClearLog.left = rcButtonStep.right + 6;
	rcButtonClearLog.top = rcButtonSolve.top;
	rcButtonClearLog.right = rcButtonClearLog.left + rcButtonSolve.right;
	rcButtonClearLog.bottom = rcButtonSolve.bottom;

	rcCheckboxGuess.left = 5;
	rcCheckboxGuess.top = rcButtonSolve.top - 5 - 20;
	rcCheckboxGuess.right = 75;
	rcCheckboxGuess.bottom = rcCheckboxGuess.top + 20;

	rcList.left = 5;
	rcList.top = 5;
	rcList.right = rcClient.right - 10;
	rcList.bottom = rcCheckboxGuess.top - 5;

	this->listLog.SetPos(rcList, SWP_NOZORDER);
	this->guessCheckBox.SetPos(rcCheckboxGuess, SWP_NOZORDER);
	this->buttonSolve.SetPos(rcButtonSolve, SWP_NOZORDER);
	this->buttonStep.SetPos(rcButtonStep, SWP_NOZORDER);
	this->buttonClearLog.SetPos(rcButtonClearLog, SWP_NOZORDER);
}

void MainWindow::OnUserMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	MineSweeperBot &bot = MineSweeperBot::GetInstance();

	switch(message)
	{
	case WM_USER_CREATED:
		CLog::Init();
		this->guessCheckBox.Check();
		bot.SetGuess(true);
		break;
	case WM_USER_SOLVE:
		if(bot.Step())
			this->PostMessage(WM_USER_SOLVE, 0, 0);
		break;
	}
}
*/