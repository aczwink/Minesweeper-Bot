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
#include "MainWindow.hpp"
//Local
#include "minesweeper_interfaces/MineSweeperXPInterface.hpp"
#include "minesweeper_interfaces/MemoryMineSweeper.hpp"

//Constructor
MainWindow::MainWindow(EventHandling::EventQueue &eventQueue) : MainAppWindow(eventQueue), log(this)
{
	this->SetTitle(u8"Minesweeper Bot");

	this->GetContentContainer()->SetLayout(new VerticalLayout);

	//top panel
	CompositeWidget* gameControlPanel = new CompositeWidget();
    gameControlPanel->SetLayout(new HorizontalLayout);
    this->AddContentChild(gameControlPanel);

    //left side
    this->gameStateView = new TextEdit();
    this->gameStateView->Editable(false);
    gameControlPanel->AddChild(this->gameStateView);

    //right side
    CompositeWidget* panel = new CompositeWidget();
    panel->SetLayout(new VerticalLayout);
    gameControlPanel->AddChild(panel);

    PushButton *connect = new PushButton();
    connect->SetText(u8"Connect");
    connect->onActivatedHandler = [this]()
    {
        this->SetupBot();
    };
    panel->AddChild(connect);

    this->solve = new PushButton();
    this->solve->SetText(u8"Solve");
    this->solve->SetEnabled(false);
    panel->AddChild(this->solve);

    this->step = new PushButton();
    this->step->SetText(u8"Step");
    this->step->SetEnabled(false);
    this->step->onActivatedHandler = [this]()
    {
        this->bot->Step();
    };
    panel->AddChild(this->step);

    this->guess = new CheckBox();
    this->guess->Text(u8"Guess");
    this->guess->SetEnabled(false);
    this->guess->toggled.Connect([this]()
    {
        this->bot->EnableGuessing(this->guess->Checked());
    });
    panel->AddChild(this->guess);

    //bottom panel
    this->logViewController = new LogViewController(this->log, this->gameStateView);
    this->logView = new ListView();
    this->logView->selectionChanged.Connect(this->logViewController.operator->(), &LogViewController::OnSelectionChanged);
    this->logView->SetController(this->logViewController);
    this->AddContentChild(this->logView);
}

//Public methods
void MainWindow::LogFieldUpdated()
{
	this->gameStateView->Text(this->log.GetNewestField());
}

void MainWindow::LogLinesUpdated()
{
	this->logViewController->ModelChanged();
}

//Private methods
void MainWindow::SetupBot()
{
	//TODO: there should be some kind of dialog that asks which interface should be used
#ifdef XPC_OS_WINDOWS
	MineSweeperInterface* interface = new MineSweeperXPInterface(this->log);
#else
	MineSweeperInterface* interface = new MemoryMineSweeper(this->log, 16, 16, 40);
#endif
	this->bot = new MineSweeperBot(interface, this->log);

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