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
#include "CLog.h"
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

void CLog::Error(CString msg)
{
	time_t timeStamp;
	tm timeFormat;
	CString message;

	timeStamp = time(NULL);
	localtime_s(&timeFormat, &timeStamp);
	message = CString(timeFormat.tm_hour) + ":" + CString(timeFormat.tm_min) + ":" + CString(timeFormat.tm_sec) + " ERROR:     " + msg;
	g_MainWindow.listLog.AddItem(message);
	g_MainWindow.listLog.SetTopIndex(g_MainWindow.listLog.GetCount() - 1);
	CLog::WriteString(message);
	m_File << endl;
}

void CLog::Field(CString caller)
{
	time_t timeStamp;
	tm timeFormat;
	MineSweeperInterface &msi = MineSweeperInterface::GetInstance();
	CString timeStr;

	timeStamp = time(NULL);
	localtime_s(&timeFormat, &timeStamp);

	timeStr = CString(timeFormat.tm_hour) + ":" + CString(timeFormat.tm_min) + ":" + CString(timeFormat.tm_sec);

	CLog::WriteString(timeStr + " INFO:     Current Field:");
	m_File << endl;

	repeat(msi.GetNoOfRows(), i)
	{
		repeat(timeStr.GetLength(), k)
		{
			CLog::WriteString(" ");
		}
		CLog::WriteString("             |");
		repeat(msi.GetNoOfColumns(), j)
		{
			switch(msi.GetBoxState(j, i))
			{
				case BOXSTATE_UNKNOWN:
					CLog::WriteString("E");
				break;
				case BOXSTATE_UNREVEALED:
					CLog::WriteString("?");
				break;
				case BOXSTATE_EMPTY:
					CLog::WriteString(" ");
				break;
				case BOXSTATE_DEFUSED:
					CLog::WriteString("!");
				break;
				case BOXSTATE_MINE:
					CLog::WriteString("X");
				break;
				case BOXSTATE_WRONGMINE:
					CLog::WriteString("#");
				break;
				case BOXSTATE_1NEARBYBOMB:
					CLog::WriteString("1");
				break;
				case BOXSTATE_2NEARBYBOMBS:
					CLog::WriteString("2");
				break;
				case BOXSTATE_3NEARBYBOMBS:
					CLog::WriteString("3");
				break;
				case BOXSTATE_4NEARBYBOMBS:
					CLog::WriteString("4");
				break;
				case BOXSTATE_5NEARBYBOMBS:
					CLog::WriteString("5");
				break;
				case BOXSTATE_6NEARBYBOMBS:
					CLog::WriteString("6");
				break;
				case BOXSTATE_7NEARBYBOMBS:
					CLog::WriteString("7");
				break;
				case BOXSTATE_8NEARBYBOMBS:
					CLog::WriteString("8");
				break;
			}
			CLog::WriteString("|");
		}
		m_File << endl;
	}

	repeat(timeStr.GetLength(), k)
	{
		CLog::WriteString(" ");
	}
	CLog::WriteString("           ");
	CLog::WriteString(caller);
	m_File << endl;
}

void CLog::Info(CString msg)
{
	time_t timeStamp;
	tm timeFormat;
	CString message;
	
	timeStamp = time(NULL);
	localtime_s(&timeFormat, &timeStamp);
	message = CString(timeFormat.tm_hour) + ":" + CString(timeFormat.tm_min) + ":" + CString(timeFormat.tm_sec) + " INFO:     " + msg;
	g_MainWindow.listLog.AddItem(message);
	g_MainWindow.listLog.SetTopIndex(g_MainWindow.listLog.GetCount() - 1);
	CLog::WriteString(message);
	m_File << endl;
}

void CLog::Init()
{
	time_t timeStamp;
	tm timeFormat;

	m_File.Open(LOG_FILENAME);
	timeStamp = time(NULL);
	localtime_s(&timeFormat, &timeStamp);
	
	CLog::WriteString("Bot started on " + CString(timeFormat.tm_mday) + "." + CString(timeFormat.tm_mon+1) + "." + CString(timeFormat.tm_year+1900) + " " + CString(timeFormat.tm_hour) + ":" + CString(timeFormat.tm_min) + ":" + CString(timeFormat.tm_sec));
	m_File << endl << endl;
}

void CLog::Warning(CString msg)
{
	time_t timeStamp;
	tm timeFormat;
	CString message;

	timeStamp = time(NULL);
	localtime_s(&timeFormat, &timeStamp);
	message = CString(timeFormat.tm_hour) + ":" + CString(timeFormat.tm_min) + ":" + CString(timeFormat.tm_sec) + " WARNING:  " + msg;
	g_MainWindow.listLog.AddItem(message);
	g_MainWindow.listLog.SetTopIndex(g_MainWindow.listLog.GetCount() - 1);
	CLog::WriteString(message);
	m_File << endl;
}
