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
#include "MineSweeperInterface.h"
//Local
#include "CLog.h"
//Namespaces
using namespace SJCLib;

//Constructor
MineSweeperInterface::MineSweeperInterface()
{
	this->pMSWnd = NULL;
	this->resolutionX = 0;
	this->resolutionY = 0;
}

//Destructor
MineSweeperInterface::~MineSweeperInterface()
{
	this->Release();
}

//Public Functions
void MineSweeperInterface::Defuse(int32 column, int32 row)
{
#ifdef _USEMOUSE
	SetForegroundWindow(this->hMsWnd);
	mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, NULL);
	mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, NULL);
#else
	int32 pos = MAKELPARAM(MINESWEEPER_LEFTSPACING + (column * MINESWEEPER_BOXSIZE) + (MINESWEEPER_BOXSIZE / 2), MINESWEEPER_TOPSPACING + (row * MINESWEEPER_BOXSIZE) + (MINESWEEPER_BOXSIZE / 2));
	this->pMSWnd->SendMessage(WM_RBUTTONDOWN, 0, pos);
	this->pMSWnd->SendMessage(WM_RBUTTONUP, 0, pos, SMTO_NORMAL, 500);
#endif
}

MineSweeperInterface &MineSweeperInterface::GetInstance()
{
	static MineSweeperInterface msi;
	return msi;
}

CDialog *MineSweeperInterface::GetWonDialog()
{
	CDialog *pDialog = (CDialog *)this->pMSWnd->GetLastActivePopup();

	if(pDialog->GetText() != MINESWEEPER_MINESWEEPERFIELDNAME)
	{
		return pDialog;
	}
	return NULL;
}

bool MineSweeperInterface::Init()
{
	this->resolutionX = GetSystemMetrics(SM_CXSCREEN);
	this->resolutionY = GetSystemMetrics(SM_CYSCREEN);
	this->pMSWnd->GetRect(&this->rcWindow);
	
	return true;
}

bool MineSweeperInterface::IsInitiated()
{
	return this->pMSWnd != NULL;
}

bool MineSweeperInterface::IsMineSweeperStillActive()
{
	return this->pMSWnd->IsWindow();
}

void MineSweeperInterface::MoveMouseOnField(int32 column, int32 row)
{
#ifdef _USEMOUSE
	POINT point;
	point.x = MINESWEEPER_LEFTSPACING + (column * MINESWEEPER_BOXSIZE) + (MINESWEEPER_BOXSIZE / 2);
	point.y = MINESWEEPER_TOPSPACING + (row * MINESWEEPER_BOXSIZE) + (MINESWEEPER_BOXSIZE / 2);
	ClientToScreen(this->hMsWnd, &point);
	this->moveMouse((ushort)point.x, (ushort)point.y);
	Sleep(50);
#endif
}

void MineSweeperInterface::Release()
{
	this->dc.Release();
	this->pMSWnd = NULL;
}

void MineSweeperInterface::Reveal(int32 column, int32 row)
{
#ifdef _USEMOUSE
	SetForegroundWindow(this->hMsWnd);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, NULL);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, NULL);
	Sleep(50);
#else
	int32 pos = MAKELPARAM(MINESWEEPER_LEFTSPACING + (column * MINESWEEPER_BOXSIZE) + (MINESWEEPER_BOXSIZE / 2), MINESWEEPER_TOPSPACING + (row * MINESWEEPER_BOXSIZE) + (MINESWEEPER_BOXSIZE / 2));
	this->pMSWnd->SendMessage(WM_LBUTTONDOWN, 0, pos);
	this->pMSWnd->SendMessage(WM_LBUTTONUP, 0, pos, SMTO_NORMAL, 50);
#endif
}

/*
//private functions
void MineSweeperInterface::MoveMouse(ushort x, ushort y)
{
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, x * MOUSE_MAXPOS / this->resolutionX, y * MOUSE_MAXPOS / this->resolutionY, 0, 0);
}

//public functions
/*void MineSweeperInterface::markBox(ushort column, ushort row)
{
	RECT rc;

	rc.left = MINESWEEPER_LEFTSPACING + (column * MINESWEEPER_BOXSIZE);
	rc.right = rc.left + MINESWEEPER_BOXSIZE;
	rc.top = MINESWEEPER_TOPSPACING + (row * MINESWEEPER_BOXSIZE);
	rc.bottom = rc.top + MINESWEEPER_BOXSIZE;
	FillRect(this->hDC, &rc, CreateSolidBrush(RGB(255, 25, 5)));
}*/
