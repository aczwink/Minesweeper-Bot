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
#include "MainWindowLogger.hpp"
#include "../model/MineSweeperBot.hpp"

//Constructor
MainWindow::MainWindow(EventHandling::EventQueue &eventQueue) : MainAppWindow(eventQueue)
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
        this->SetupInterface();
    };
    panel->AddChild(connect);

    this->solve = new PushButton();
    this->solve->SetText(u8"Solve");
    this->solve->SetEnabled(false);
    this->solve->onActivatedHandler = [this]()
    {
        while(this->interface->QueryState().ComputePlayingState() == PlayingState::Active)
            this->Step();
    };
    panel->AddChild(this->solve);

    this->step = new PushButton();
    this->step->SetText(u8"Step");
    this->step->SetEnabled(false);
    this->step->onActivatedHandler = [this]()
    {
        this->Step();
    };
    panel->AddChild(this->step);

    this->guess = new CheckBox();
    this->guess->Text(u8"Guess");
    this->guess->SetEnabled(false);
    panel->AddChild(this->guess);

    //bottom panel
    this->logView = new ListView();
    this->logView->selectionChanged.Connect(this, &MainWindow::OnLogSelectionChanged);
    this->AddContentChild(this->logView);
}

//Public methods
void MainWindow::LogLinesUpdated()
{
    if(!this->logViewController.IsNull())
    {
        this->logViewController->ModelChanged();
        this->logView->Select(this->logViewController->GetNewestLineIndex());
    }
}

//Private methods
void MainWindow::SetupInterface()
{
#ifdef XPC_OS_WINDOWS
    this->interface = new MineSweeperXPInterface(this->log);
#else
    this->interface = new MemoryMineSweeper(16, 16, 40);
#endif
    this->logger = new MainWindowLogger(*this, *this->interface);

    this->logViewController = new LogViewController(*this->logger);
    this->logView->SetController(this->logViewController);

    this->logger->Info(u8"Successfully connected");

    this->solve->SetEnabled(true);
    this->step->SetEnabled(true);
    this->guess->SetEnabled(true);
}

void MainWindow::Step()
{
    MineSweeperBot bot(*this->interface, *this->logger);
    bot.EnableGuessing(this->guess->Checked());
    bot.Step();
}

//Event handlers
void MainWindow::OnLogSelectionChanged()
{
    auto selection = this->logView->SelectionController().GetSelectedIndexes();
    if(selection.IsEmpty())
        this->gameStateView->Text(u8"");
    else
        this->gameStateView->Text(this->logger->GetField(selection[0].GetRow()));
}