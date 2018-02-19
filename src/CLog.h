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
//SJCLib
#include <SJCLib.h>
//Namespaces
using namespace SJCLib;
//Definitions
#define LOG_FILENAME "bot.log"
#define LOGERROR(msg) CLog::Error((CString)msg + " [" + GetFullFileName(__FILE__) + ", " + __FUNCTION__ + "(), " + CString(__LINE__) + "]");
#define LOGFIELD() CLog::Field("[" + GetFullFileName(__FILE__) + ", " + __FUNCTION__ + "(), " + CString(__LINE__) + "]");
#define LOGINFO(msg) CLog::Info((CString)msg + " [" + GetFullFileName(__FILE__) + ", " + __FUNCTION__ + "(), " + CString(__LINE__) + "]");
#define LOGWARNING(msg) CLog::Warning((CString)msg + " [" + GetFullFileName(__FILE__) + ", " + __FUNCTION__ + "(), " + CString(__LINE__) + "]");

class CLog
{
private:
	//Variables
	static COFStream m_File;
	//Functions
	static void WriteString(CString refMsg);
public:
	//Functions
	static void Close();
	static void Error(CString msg);
	static void Field(CString caller);
	static void Info(CString msg);
	static void Init();
	static void Warning(CString msg);
};