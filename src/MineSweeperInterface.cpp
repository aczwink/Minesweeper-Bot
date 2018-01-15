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

//Private Functions
uint32 MineSweeperInterface::GetBoxPixelChecksum(uint16 column, uint16 row)
{
	uint32 checksum = 0;
	BITMAPINFO bi;
	CPointer<CBitmap> bmp, oldBmp;
	CPointer<CDeviceContext> memDC;
	byte *pMemory;

	MemZero(&bi, sizeof(bi));

	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = MINESWEEPER_BOXSIZE;
	bi.bmiHeader.biHeight = -MINESWEEPER_BOXSIZE;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 24;

	bmp = this->dc->CreateDIBSection(&bi, DIB_RGB_COLORS, (void **)&pMemory);
	memDC = this->dc->CreateCompatibleDC();
	oldBmp = memDC->SelectObject(bmp);
	memDC->BitBlt(0, 0, MINESWEEPER_BOXSIZE, MINESWEEPER_BOXSIZE, *this->dc, MINESWEEPER_LEFTSPACING + (column * MINESWEEPER_BOXSIZE), MINESWEEPER_TOPSPACING + (row * MINESWEEPER_BOXSIZE), SRCCOPY);
	
	for(int32 i = 0; i < MINESWEEPER_BOXSIZE * MINESWEEPER_BOXSIZE * 3; i+=3)
	{
		checksum += pMemory[i];
		checksum += pMemory[i+1];
		checksum += pMemory[i+2];
	}
	return checksum;
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

EBoxState MineSweeperInterface::GetBoxState(uint16 column, uint16 row)
{
	uint32 boxChecksum;
	
	if((column < 0) || (row < 0) || (column > this->GetNoOfColumns()-1) || (row > this->GetNoOfRows()-1))
		return BOXSTATE_NOTEXISTENT;
	
	boxChecksum = this->GetBoxPixelChecksum(column, row);

	switch(boxChecksum)
	{
		case MINESWEEPER_BOXCHECKSUMS_UNREVEALED:
			return BOXSTATE_UNREVEALED;
		break;
		case MINESWEEPER_BOXCHECKSUMS_EMPTY:
			return BOXSTATE_EMPTY;
		break;
		case MINESWEEPER_BOXCHECKSUMS_DEFUSED:
			return BOXSTATE_DEFUSED;
		break;
		case MINESWEEPER_BOXCHECKSUMS_ACTIVEMINE:
		case MINESWEEPER_BOXCHECKSUMS_MINE:
			return BOXSTATE_MINE;
		break;
		case MINESWEEPER_BOXCHECKSUMS_WRONGMINE:
			return BOXSTATE_WRONGMINE;
		break;
		case MINESWEEPER_BOXCHECKSUMS_1NEARBYBOMB:
			return BOXSTATE_1NEARBYBOMB;
		break;
		case MINESWEEPER_BOXCHECKSUMS_2NEARBYBOMBS:
			return BOXSTATE_2NEARBYBOMBS;
		break;
		case MINESWEEPER_BOXCHECKSUMS_3NEARBYBOMBS:
			return BOXSTATE_3NEARBYBOMBS;
		break;
		case MINESWEEPER_BOXCHECKSUMS_4NEARBYBOMBS:
			return BOXSTATE_4NEARBYBOMBS;
		break;
		case MINESWEEPER_BOXCHECKSUMS_5NEARBYBOMBS:
			return BOXSTATE_5NEARBYBOMBS;
		break;
		case MINESWEEPER_BOXCHECKSUMS_6NEARBYBOMBS:
			return BOXSTATE_6NEARBYBOMBS;
		break;
		case MINESWEEPER_BOXCHECKSUMS_7NEARBYBOMBS:
			return BOXSTATE_7NEARBYBOMBS;
		break;
		case MINESWEEPER_BOXCHECKSUMS_8NEARBYBOMBS:
			return BOXSTATE_8NEARBYBOMBS;
		break;
	}

	LOGERROR("Interface couldn't detect field [" + CString(column) + "|" + CString(row) + "]. The checksum of the field is: " + CString(boxChecksum));

	return BOXSTATE_UNKNOWN;
}

MineSweeperInterface &MineSweeperInterface::GetInstance()
{
	static MineSweeperInterface msi;
	return msi;
}

uint32 MineSweeperInterface::GetNoOfColumns()
{
	return (this->rcClient.right - MINESWEEPER_LEFTSPACING - MINESWEEPER_RIGHTSPACING) / MINESWEEPER_BOXSIZE;
}

uint32 MineSweeperInterface::GetNoOfRows()
{
	return (this->rcClient.bottom - MINESWEEPER_TOPSPACING - MINESWEEPER_BOTTOMSPACING) / MINESWEEPER_BOXSIZE;
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
	this->pMSWnd = CWindow::FindWindow(CString(), MINESWEEPER_WINDOWNAME);
	if(!this->pMSWnd)
		return false;
	this->resolutionX = GetSystemMetrics(SM_CXSCREEN);
	this->resolutionY = GetSystemMetrics(SM_CYSCREEN);
	this->pMSWnd->GetRect(&this->rcWindow);
	this->pMSWnd->GetClientRect(&this->rcClient);
	this->dc = this->pMSWnd->GetDC();
	
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
