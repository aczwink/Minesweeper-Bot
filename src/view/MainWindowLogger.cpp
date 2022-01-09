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
#include "MainWindowLogger.hpp"

//Public methods
String MainWindowLogger::GetField(uint32 lineNumber) const
{
    return this->logFields[lineNumber];
}

String MainWindowLogger::GetLine(uint32 lineNumber) const
{
    return this->logLines[lineNumber];
}

uint32 MainWindowLogger::GetNumberOfLines() const
{
    return this->logLines.GetNumberOfElements();
}

void MainWindowLogger::Info(const String& text)
{
    String line = this->GetTime() + u8" INFO:     " + text;
    this->logLines.Push(line);
    this->logFields.Push(this->mineSweeperInterface.QueryState().ToString());
    this->mainWindow.LogLinesUpdated();
}