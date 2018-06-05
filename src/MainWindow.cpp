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
//Local
#include "MineSweeperXPInterface.hpp"

//Constructor
MainWindow::MainWindow(EventQueue &eventQueue) : MainAppWindow(eventQueue)
{
	this->SetTitle(u8"Minesweeper Bot");

	this->SetLayout(new VerticalLayout);

	//top panel
	WidgetContainer *gameControlPanel = new WidgetContainer(this);
	gameControlPanel->SetLayout(new HorizontalLayout);
	//left side
	this->gameStateView = new TextEdit(gameControlPanel);
	this->gameStateView->SetEditable(false);
	//right side
	WidgetContainer *panel = new WidgetContainer(gameControlPanel);
	panel->SetLayout(new VerticalLayout);

	PushButton *solve = new PushButton(panel);
	solve->SetText(u8"Solve");

	PushButton *step = new PushButton(panel);
	step->SetText(u8"Step");
	step->onActivatedHandler = [this]()
	{
		this->bot->Step();
	};

	PushButton *clearLog = new PushButton(panel);
	clearLog->SetText(u8"Clear Log");

	CheckBox *guess = new CheckBox(panel);
	guess->SetText(u8"Guess");

	//bottom panel
	ListView *log = new ListView(this);

	this->bot = new MineSweeperBot(new MineSweeperXPInterface(this->log), this->log);
}

/*
//Local
#include "CLog.h"
#include "MineSweeperBot.h"
#include "resource.h"

//Message-callbacks
bool MainWindow::OnCreate()
{
	this->PostMessageA(WM_USER_CREATED, 0, 0);
}

void MainWindow::OnDestroy()
{
	MineSweeperBot &bot = MineSweeperBot::GetInstance();

	LOGINFO("Program end");
	bot.Release();
	CLog::Close();
	PostQuitMessage(EXIT_SUCCESS);
}
*/