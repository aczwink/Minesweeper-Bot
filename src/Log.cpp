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
//Class Header
#include "Log.hpp"
//Local
#include "MainWindow.hpp"

//Constructor
Log::Log(MainWindow *mainWindow) : mainWindow(mainWindow)
{
}

//Public methods
void Log::Error(const String &msg, const char *filename, const char *functionname, int lineno)
{
	String line = this->GetTime() + u8" ERROR:     " + msg + u8" [" + filename + u8", " + functionname + u8"(), " + String::Number(lineno) + u8"]";
	this->logLines.Push(line);
	this->mainWindow->LogLinesUpdated();
}

void Log::Field(const String &fieldString)
{
	this->logFields[this->logLines.GetNumberOfElements()] = fieldString;
	this->mainWindow->LogFieldUpdated();
}

String Log::GetField(uint32 index) const
{
	while (index != Natural<uint32>::Max())
	{
		auto it = this->logFields.Find(index);
		if (it != this->logFields.end())
			return (*it).value;
		index--;
	}

	return String();
}

void Log::Info(const String &msg, const char *filename, const char *functionname, int lineno)
{
	String line = this->GetTime() + u8" INFO:     " + msg + u8" [" + filename + u8", " + functionname + u8"(), " + String::Number(lineno) + u8"]";
	this->logLines.Push(line);
	this->mainWindow->LogLinesUpdated();
}

void Log::Warning(const String &msg, const char *filename, const char *functionname, int lineno)
{
	String line = this->GetTime() + u8" WARNING:  " + msg + u8" [" + filename + u8", " + functionname + u8"(), " + String::Number(lineno) + u8"]";
	this->logLines.Push(line);
	this->mainWindow->LogLinesUpdated();
}
	/*
	time_t timeStamp;
	tm timeFormat;

	timeStamp = time(NULL);
	localtime_s(&timeFormat, &timeStamp);

	CString(timeFormat.tm_mday) + "." + CString(timeFormat.tm_mon + 1) + "." + CString(timeFormat.tm_year + 1900) + " " + CString(timeFormat.tm_hour) + ":" + CString(timeFormat.tm_min) + ":" + CString(timeFormat.tm_sec)
	*/

/*
//Global
#include <ctime>
//Local
#include "globals.h"
#include "MineSweeperInterface.h"
//Namespaces
using namespace SJCLib;

//Class Variables
COFStream CLog::m_File;

//Private Functions
void CLog::WriteString(CString refMsg)
{
	m_File.WriteString(refMsg);
	m_File.Flush();
}

//Public Functions
void CLog::Close()
{
	m_File.Close();
}
*/