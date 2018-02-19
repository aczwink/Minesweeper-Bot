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
#pragma once
//SJC Libs
#include <SJCWinLib.h>
//Namespaces
using namespace SJCWinLib;

class CCheckBoxGuess : public CCheckBox
{
private:
	//Message-callbacks
	void OnClick();
};

class CButtonSolve : public CButton
{
private:
	//Message-callbacks
	void OnClick();
};

class CButtonStep : public CButton
{
private:
	//Message-callbacks
	void OnClick();
};

class CButtonClearLog : public CButton
{
private:
	//Message-callbacks
	void OnClick();
};