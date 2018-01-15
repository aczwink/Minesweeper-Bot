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
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#include "version.h" //Only here

//Definitions
#define __STR(x) #x
#define _STR(x) __STR(x)

#define APPLICATION_NAME "MineSweeper Bot XP"
#define APPLICATION_CREATOR "SoulJammingCurse"
#define APPLICATION_CREATOR_WEBSITE "http://souljammingcurse.de"
#define APPLICATION_ORIGINALFILENAME "MineSweeper Bot XP.exe"
#define APPLICATION_VERSION_RESOURCE VERSION_MAJOR,VERSION_MINOR,VERSION_BUILD,VERSION_REVISION
#define APPLICATION_VERSION_STRING _STR(VERSION_MAJOR) "." _STR(VERSION_MINOR) "." _STR(VERSION_BUILD) "." _STR(VERSION_REVISION)

#define APPLICATION_WNDCLASS APPLICATION_NAME

#ifdef _DEBUG
#define APPLICATION_TITLE APPLICATION_NAME " by " APPLICATION_CREATOR " v" APPLICATION_VERSION_STRING " Build:" BUILDDATE_STRING " Debug Mode"
#else
#define APPLICATION_TITLE APPLICATION_NAME " by " APPLICATION_CREATOR " v" APPLICATION_VERSION_STRING " Build:" BUILDDATE_STRING
#endif

//Messages
#define WM_USER_CREATED WM_USER+1
#define WM_USER_SOLVE WM_USER+2
