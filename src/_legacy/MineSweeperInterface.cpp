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

void MineSweeperInterface::Release()
{
	this->dc.Release();
	this->pMSWnd = NULL;
}

/*
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
