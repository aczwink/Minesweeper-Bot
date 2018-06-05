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
#include "MineSweeperBot.hpp"

class MainWindow : public MainAppWindow
{
public:
	//Constructor
	MainWindow(EventQueue &eventQueue);

private:
	//Members
	Log log;
	UniquePointer<MineSweeperBot> bot;
	TextEdit *gameStateView;
};
/*
//SJC Libs
#include <SJCWinLib.h>
//Local
#include "buttons.h"
//Namespaces
using namespace SJCWinLib;

class MainWindow : public CWindow
{
	friend class CLog;
	friend class CButtonClearLog;
private:
	//Variables
	CListBox listLog;
	//Message-callbacks
	bool OnCreate();
	void OnDestroy();
	void OnUserMessage(UINT message, WPARAM wParam, LPARAM lParam);
};
*/
