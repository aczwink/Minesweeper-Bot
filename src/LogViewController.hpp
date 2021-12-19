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
#include "Log.hpp"

class LogViewController : public ListController
{
public:
	//Constructor
	inline LogViewController(const Log &log, TextEdit *&logEntryView) : log(log), logEntryView(logEntryView)
	{
	}

	//Methods
	uint32 GetNumberOfItems() const override;
	String GetText(uint32 index) const override;

	//Eventhandlers
	void OnSelectionChanged();

private:
	//Members
	const Log &log;
	TextEdit *&logEntryView;
};