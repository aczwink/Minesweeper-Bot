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
//SJC Libs
#include <SJCWinLib.h>
//Local
#include "globals.h"
#include "resource.h"
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;

//Global Variables
CModule g_Module;
CMainWindow g_MainWindow;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CApplication app;
	CBrush backgroundBrush;
	CIcon icon;

#ifdef _DEBUG
	CWindow *pConsole;

	AllocateConsole();

	pConsole = CWindow::GetConsoleWindow();
	pConsole->SetText("MineSweeper Bot Debug Console");
	pConsole->Move(0, 0, 500, 300);

	stdOut << "Launching in Debug Mode" << endl;
#endif

	g_Module.Attach(hInstance);
	backgroundBrush.CreateSystemColorBrush(COLOR_WINDOW);
	icon.LoadSystemIcon(IDI_APPLICATION);
	if(!g_Module.RegisterWindowClass(&backgroundBrush, LoadCursor(NULL, IDC_ARROW), &icon, &icon, APPLICATION_WNDCLASS))
		return EXIT_FAILURE;

	g_MainWindow.Create(APPLICATION_WNDCLASS, APPLICATION_TITLE, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 200, g_Module);
	g_MainWindow.Show(nCmdShow);

	return app.Run();
}
