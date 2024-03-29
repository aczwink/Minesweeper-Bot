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
#ifdef XPC_OS_WINDOWS
//Class header
#include "MineSweeperXPInterface.hpp"

//Constants
#define MINESWEEPER_LEFTSPACING 12
#define MINESWEEPER_RIGHTSPACING 8
#define MINESWEEPER_TOPSPACING 55
#define MINESWEEPER_BOTTOMSPACING MINESWEEPER_RIGHTSPACING
#define MINESWEEPER_BOXSIZE 16

#define MINESWEEPER_BOXCHECKSUMS_UNREVEALED 0x23F5E

#define MINESWEEPER_WINDOWNAME L"Minesweeper"

#define MOUSE_MAXPOS 65535

//Destructor
MineSweeperXPInterface::~MineSweeperXPInterface()
{
	ReleaseDC(this->hMSWnd, this->hDC);
}

//Public methods
void MineSweeperXPInterface::Defuse(uint32 column, uint32 row)
{
	this->MoveMouseOverField(column, row);
#ifdef _USEMOUSE
	SetForegroundWindow(this->hMsWnd);
	mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, NULL);
	mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, NULL);
#else
	int32 pos = MAKELPARAM(MINESWEEPER_LEFTSPACING + (column * MINESWEEPER_BOXSIZE) + (MINESWEEPER_BOXSIZE / 2), MINESWEEPER_TOPSPACING + (row * MINESWEEPER_BOXSIZE) + (MINESWEEPER_BOXSIZE / 2));
	SendMessageW(this->hMSWnd, WM_RBUTTONDOWN, 0, pos);
	PDWORD_PTR result;
	SendMessageTimeoutW(this->hMSWnd, WM_RBUTTONUP, 0, pos, SMTO_NORMAL, 500, nullptr);
#endif
}

BoxState MineSweeperXPInterface::GetBoxState(uint16 row, uint16 col) const
{
	uint32 boxChecksum;

	if ((col < 0) || (row < 0) || (col > this->GetNumberOfColumns() - 1) || (row > this->GetNumberOfRows() - 1))
		NOT_IMPLEMENTED_ERROR; //TODO: throw exception here

	boxChecksum = this->GetBoxPixelChecksum(col, row);

	switch (boxChecksum)
	{
	case MINESWEEPER_BOXCHECKSUMS_UNREVEALED:
		return BoxState::Unrevealed;
		/*
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
		break;*/
	}

	LOG_ERROR("Interface couldn't detect field [" + String::Number(col) + "|" + String::Number(row) + "]. The checksum of the field is: " + String::Number(boxChecksum));

	return BoxState::Unknown;
}

uint16 MineSweeperXPInterface::GetNumberOfColumns() const
{
	return (this->rcClient.right - MINESWEEPER_LEFTSPACING - MINESWEEPER_RIGHTSPACING) / MINESWEEPER_BOXSIZE;
}

uint16 MineSweeperXPInterface::GetNumberOfRows() const
{
	return (this->rcClient.bottom - MINESWEEPER_TOPSPACING - MINESWEEPER_BOTTOMSPACING) / MINESWEEPER_BOXSIZE;
}

void MineSweeperXPInterface::Reveal(uint32 column, uint32 row)
{
	this->MoveMouseOverField(column, row);
#ifdef _USEMOUSE
	SetForegroundWindow(this->hMsWnd);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, NULL);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, NULL);
	Sleep(50);
#else
	int32 pos = MAKELPARAM(MINESWEEPER_LEFTSPACING + (column * MINESWEEPER_BOXSIZE) + (MINESWEEPER_BOXSIZE / 2), MINESWEEPER_TOPSPACING + (row * MINESWEEPER_BOXSIZE) + (MINESWEEPER_BOXSIZE / 2));
	SendMessageW(this->hMSWnd, WM_LBUTTONDOWN, 0, pos);
	SendMessageTimeoutW(this->hMSWnd, WM_LBUTTONUP, 0, pos, SMTO_NORMAL, 50, nullptr);
#endif
}

//Private methods
bool MineSweeperXPInterface::Connect()
{
	this->hMSWnd = ::FindWindowW(nullptr, MINESWEEPER_WINDOWNAME);
	if (!this->hMSWnd)
		return false;

	GetClientRect(this->hMSWnd, &this->rcClient);

	this->hDC = GetDC(this->hMSWnd);

	return true;
}

uint32 MineSweeperXPInterface::GetBoxPixelChecksum(uint16 column, uint16 row) const
{
	uint32 checksum = 0;
	BITMAPINFO bi;
	HBITMAP bmp;
	HDC memDC;
	byte *pMemory;

	MemZero(&bi, sizeof(bi));

	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = MINESWEEPER_BOXSIZE;
	bi.bmiHeader.biHeight = -MINESWEEPER_BOXSIZE;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 24;

	bmp = CreateDIBSection(this->hDC, &bi, DIB_RGB_COLORS, (void **)&pMemory, NULL, 0);
	memDC = CreateCompatibleDC(this->hDC);
	HGDIOBJ oldBmp = SelectObject(memDC, bmp);
	BitBlt(memDC, 0, 0, MINESWEEPER_BOXSIZE, MINESWEEPER_BOXSIZE, this->hDC, MINESWEEPER_LEFTSPACING + (column * MINESWEEPER_BOXSIZE), MINESWEEPER_TOPSPACING + (row * MINESWEEPER_BOXSIZE), SRCCOPY);

	for (int32 i = 0; i < MINESWEEPER_BOXSIZE * MINESWEEPER_BOXSIZE * 3; i += 3)
	{
		checksum += pMemory[i];
		checksum += pMemory[i + 1];
		checksum += pMemory[i + 2];
	}

	DeleteObject(oldBmp);
	DeleteDC(memDC);
	DeleteObject(bmp);
	
	return checksum;
}

void MineSweeperXPInterface::MoveMouseOverField(uint32 column, uint32 row)
{
	POINT point;
	point.x = MINESWEEPER_LEFTSPACING + (column * MINESWEEPER_BOXSIZE) + (MINESWEEPER_BOXSIZE / 2);
	point.y = MINESWEEPER_TOPSPACING + (row * MINESWEEPER_BOXSIZE) + (MINESWEEPER_BOXSIZE / 2);
	ClientToScreen(this->hMSWnd, &point);
	this->MoveMouseTo((uint16)point.x, (uint16)point.y);
	StdPlusPlus::Sleep(50 * 1000 * 1000);
}

void MineSweeperXPInterface::MoveMouseTo(uint16 x, uint16 y)
{
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, x * MOUSE_MAXPOS / this->resolutionX, y * MOUSE_MAXPOS / this->resolutionY, 0, 0);
}
#endif