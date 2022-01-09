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
//Class Header
#include "Log.hpp"

//Public methods
void Log::Error(const String &msg, const char *filename, const char *functionname, int lineno)
{
	String line = this->GetTime() + u8" ERROR:     " + msg + u8" [" + filename + u8", " + functionname + u8"(), " + String::Number(lineno) + u8"]";
	this->logLines.Push(line);
	this->mainWindow->LogLinesUpdated();
}

void Log::Field(const String &fieldString)
{
	this->logFields[this->logLines.GetNumberOfElements() - 1] = fieldString;
	this->mainWindow->LogFieldUpdated();
}

String Log::GetField(uint32 index) const
{
	while (index != Unsigned<uint32>::Max())
	{
		auto it = this->logFields.Find(index);
		if (it != this->logFields.end())
			return (*it).value;
		index--;
	}

	return String();
}

void Log::Warning(const String &msg, const char *filename, const char *functionname, int lineno)
{
	String line = this->GetTime() + u8" WARNING:  " + msg + u8" [" + filename + u8", " + functionname + u8"(), " + String::Number(lineno) + u8"]";
	this->logLines.Push(line);
	this->mainWindow->LogLinesUpdated();
}