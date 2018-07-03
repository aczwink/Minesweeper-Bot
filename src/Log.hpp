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
#include <Std++.hpp>
using namespace StdPlusPlus;
using namespace StdPlusPlus::UI;

//Forward declarations
class MainWindow;

class Log
{
public:
	//Constructor
	Log(MainWindow *mainWindow);

	//Methods
	void Error(const String &msg, const char *filename, const char *functionname, int lineno);
	void Field(const String &fieldString);
	String GetField(uint32 index) const;
	void Info(const String &msg, const char *filename, const char *functionname, int lineno);
	void Warning(const String &msg, const char *filename, const char *functionname, int lineno);

	//Inline
	inline const DynamicArray<String> &GetLines() const
	{
		return this->logLines;
	}

	inline String GetNewestField() const
	{
		if (this->logFields.IsEmpty())
			return String();
		auto it = this->logFields.end();
		--it;
		return (*it).value;
	}

private:
	//Members
	MainWindow * mainWindow;
	DynamicArray<String> logLines;
	Map<uint32, String> logFields;

	//Methods
	void WriteString(const String &msg);

	//Inline
	inline String GetTime() const
	{
		DateTime t = DateTime::Now();
		return TimeZone::GetUserLocalTimeZone().Translate(t).ToISOString();
	}
};

#define LOG_ERROR(msg) this->log.Error(msg, __FILE__, __FUNCTION__, __LINE__);
#define LOG_INFO(msg) this->log.Info(msg, __FILE__, __FUNCTION__, __LINE__);
#define LOG_WARNING(msg) this->log.Warning(msg, __FILE__, __FUNCTION__, __LINE__);
/*
//SJCLib
#include <SJCLib.h>
//Namespaces
using namespace SJCLib;
//Definitions
#define LOGFIELD() CLog::Field("[" + GetFullFileName(__FILE__) + ", " + __FUNCTION__ + "(), " + CString(__LINE__) + "]");

class CLog
{
private:
	//Variables
	static COFStream m_File;
public:
	//Functions
	static void Close();
	static void Field(CString caller);
	static void Info(CString msg);
	static void Init();
};
*/