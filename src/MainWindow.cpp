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
MainWindow::MainWindow(EventQueue &eventQueue) : MainAppWindow(eventQueue), log(this), logViewController(this->log, this->gameStateView)
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

	PushButton *connect = new PushButton(panel);
	connect->SetText(u8"Connect");
	connect->onActivatedHandler = [this]()
	{
		this->SetupBot();
	};

	this->solve = new PushButton(panel);
	this->solve->SetText(u8"Solve");
	this->solve->SetEnabled(false);

	this->step = new PushButton(panel);
	this->step->SetText(u8"Step");
	this->step->SetEnabled(false);
	this->step->onActivatedHandler = [this]()
	{
		this->bot->Step();
	};

	this->guess = new CheckBox(panel);
	this->guess->SetText(u8"Guess");
	this->guess->SetEnabled(false);
	this->guess->onToggledHandler = [this]()
	{
		this->bot->EnableGuessing(this->guess->IsChecked());
	};

	//bottom panel
	this->logView = new ListView(this);
	this->logView->SetController(this->logViewController);
}

//Public methods
void MainWindow::LogFieldUpdated()
{
	this->gameStateView->SetText(this->log.GetNewestField());
}

void MainWindow::LogLinesUpdated()
{
	this->logView->GetController()->ModelChanged();
}

//Private methods
void MainWindow::SetupBot()
{
	//TODO: there should be some kind of dialog that asks which interface should be used
	this->bot = new MineSweeperBot(new MineSweeperXPInterface(this->log), this->log);

	LOG_INFO(u8"Successfully connected");
	this->bot->LogField();

	this->solve->SetEnabled(true);
	this->step->SetEnabled(true);
	this->guess->SetEnabled(true);
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