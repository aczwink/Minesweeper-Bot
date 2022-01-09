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
#include "../minesweeper_interfaces/MemoryMineSweeper.hpp"
#include "../model/MovesLogger.hpp"
#include "LogViewController.hpp"

class MainWindow : public MainAppWindow
{
public:
    //Constructor
    MainWindow(EventHandling::EventQueue &eventQueue);

    //Methods
    void LogLinesUpdated();

private:
    //Members
    TextEdit *gameStateView;
    PushButton *solve;
    PushButton *step;
    CheckBox *guess;
    ListView *logView;
    SharedPointer<LogViewController> logViewController;
    UniquePointer<MovesLogger> logger;
    UniquePointer<MineSweeperInterface> interface;

    //Methods
    void SetupInterface();
    void Step();

    //Event handlers
    void OnLogSelectionChanged();
};