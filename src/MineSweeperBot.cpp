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
#include "MineSweeperBot.hpp"

//Constructor
MineSweeperBot::MineSweeperBot(UniquePointer<MineSweeperInterface> &&msInterface, Log &log) : msInterface(Move(msInterface)), log(log)
{
	this->maxMoves = 0;
}

//Public methods
bool MineSweeperBot::CanContinue()
{
	if (this->maxMoves <= 0)
	{
		LOG_WARNING(u8"Maximum number of runs exceeded");
		return false;
	}
}

void MineSweeperBot::Step()
{
	ASSERT(this->CanContinue(), u8"You called MineSweeperBot::Step though bot can't continue");

	this->maxMoves--;
	NOT_IMPLEMENTED_ERROR; //TODO
}
/*
//SJC Libs
#include <SJCWinLib.h>
//Local
#include "CLog.h"
//Namespaces
using namespace SJCWinLib;

//Constructor
MineSweeperBot::MineSweeperBot()
{
	CLog::Init();

	this->columns = 0;
	this->guess = 0;
	this->isInitiated = false;
	this->ppFields = NULL;
	this->rows = 0;
}

//Destructor
MineSweeperBot::~MineSweeperBot()
{
	if(this->ppFields)
		this->Release();
}

//Private Functions
bool MineSweeperBot::DoMove()
{
	MineSweeperInterface &msi = MineSweeperInterface::GetInstance();
	CArray<SField> surroundingBoxes;
	uint16 nearbyMines;
	uint16 unrevealedBoxCount;
	uint16 defusedBoxCount;
	uint16 resultingNearbyMines;

	repeat(this->rows, row)
	{
		repeat(this->columns, column)
		{
			switch(this->ppFields[row][column])
			{
				case BOXSTATE_1NEARBYBOMB:
					nearbyMines = 1;
				break;
				case BOXSTATE_2NEARBYBOMBS:
					nearbyMines = 2;
				break;
				case BOXSTATE_3NEARBYBOMBS:
					nearbyMines = 3;
				break;
				case BOXSTATE_4NEARBYBOMBS:
					nearbyMines = 4;
				break;
				case BOXSTATE_5NEARBYBOMBS:
					nearbyMines = 5;
				break;
				case BOXSTATE_6NEARBYBOMBS:
					nearbyMines = 6;
				break;
				case BOXSTATE_7NEARBYBOMBS:
					nearbyMines = 7;
				break;
				case BOXSTATE_8NEARBYBOMBS:
					nearbyMines = 8;
				break;
				default:
					continue;
				break;
			}
			
			unrevealedBoxCount = 0;
			defusedBoxCount = 0;
			resultingNearbyMines = 0;
			surroundingBoxes.Release();
			this->GetSurroundingBoxes(column, row, surroundingBoxes);
			
			repeat(surroundingBoxes.GetLength(), b)
			{
				if(surroundingBoxes[b].state == BOXSTATE_UNREVEALED)
				{
					unrevealedBoxCount++;
				}
				if(surroundingBoxes[b].state == BOXSTATE_DEFUSED)
				{
					defusedBoxCount++;
				}
			}

			resultingNearbyMines = nearbyMines - defusedBoxCount;
			if(resultingNearbyMines == 0) //all nearby mines have been defused... reveal all unrevealed boxes
			{
				repeat(surroundingBoxes.GetLength(), b)
				{
					if(surroundingBoxes[b].state == BOXSTATE_UNREVEALED)
					{
						LOGINFO("Revealing [" + CString(surroundingBoxes[b].column) + "|" + CString(surroundingBoxes[b].row) + "]");
						msi.MoveMouseOnField(surroundingBoxes[b].column, surroundingBoxes[b].row);
						msi.Reveal(surroundingBoxes[b].column, surroundingBoxes[b].row);
						return true; //successfull move
					}
				}
			}
			if(unrevealedBoxCount == resultingNearbyMines) //same amount of unrevealed boxes and nearby mines... AND ... there are less defused fields than nearby mines
			{
				repeat(surroundingBoxes.GetLength(), b)
				{
					if(surroundingBoxes[b].state == BOXSTATE_UNREVEALED)
					{
						LOGINFO("Defusing [" + CString(surroundingBoxes[b].column) + "|" + CString(surroundingBoxes[b].row) + "]");
						msi.MoveMouseOnField(surroundingBoxes[b].column, surroundingBoxes[b].row);
						msi.Defuse(surroundingBoxes[b].column, surroundingBoxes[b].row);
						return true; //successfull move
					}
				}
			}
		}
	}
	return false;
}

void MineSweeperBot::EnterName()
{
	CDialog *pWonDialog, *pBestListDialog;
	MineSweeperInterface &msi = MineSweeperInterface::GetInstance();
	
	pWonDialog = msi.GetWonDialog();
	if(pWonDialog)
	{
		CEdit *pNameControl;
		CButton *pOKButton;

		pNameControl = (CEdit *)pWonDialog->GetNextGroupItem(NULL);
		pOKButton = (CButton *)pWonDialog->GetNextGroupItem(pNameControl);

		pNameControl->SetText("SJC's Bot");
		pOKButton->Click();

		Sleep(50);
		pBestListDialog = msi.GetWonDialog();

		pOKButton = (CButton *)pBestListDialog->GetNextGroupItem(NULL);
		pOKButton->Click();

		LOGINFO("Signed in the bestlist ;)");
	}
}

void MineSweeperBot::GetSurroundingBoxes(uint16 column, uint16 row, CArray<SField> &surroundingBoxes)
{
	MineSweeperInterface &msi = MineSweeperInterface::GetInstance();
	SField f;

	f.column = column-1;
	f.row = row-1;
	if(f.column >= 0 && f.row >= 0)
	{
		f.state = this->ppFields[f.row][f.column];
		if(f.state != BOXSTATE_NOTEXISTENT)
		{
			surroundingBoxes.Push(f);
		}
	}

	f.column = column;
	f.row = row-1;
	if(f.row >= 0)
	{
		f.state = this->ppFields[f.row][f.column];
		if(f.state != BOXSTATE_NOTEXISTENT)
		{
			surroundingBoxes.Push(f);
		}
	}

	f.column = column+1;
	f.row = row-1;
	if(f.row >= 0 && f.column < this->columns)
	{
		f.state = this->ppFields[f.row][f.column];
		if(f.state != BOXSTATE_NOTEXISTENT)
		{
			surroundingBoxes.Push(f);
		}
	}

	f.column = column-1;
	f.row = row;
	if(f.column >= 0)
	{
		f.state = this->ppFields[f.row][f.column];
		if(f.state != BOXSTATE_NOTEXISTENT)
		{
			surroundingBoxes.Push(f);
		}
	}

	f.column = column+1;
	f.row = row;
	if(f.column < this->columns)
	{
		f.state = this->ppFields[f.row][f.column];
		if(f.state != BOXSTATE_NOTEXISTENT)
		{
			surroundingBoxes.Push(f);
		}
	}

	f.column = column-1;
	f.row = row+1;
	if(f.column >= 0 && f.row < this->rows)
	{
		f.state = this->ppFields[f.row][f.column];
		if(f.state != BOXSTATE_NOTEXISTENT)
		{
			surroundingBoxes.Push(f);
		}
	}

	f.column = column;
	f.row = row+1;
	if(f.row < this->rows)
	{
		f.state = this->ppFields[f.row][f.column];
		if(f.state != BOXSTATE_NOTEXISTENT)
		{
			surroundingBoxes.Push(f);
		}
	}

	f.column = column+1;
	f.row = row+1;
	if(f.column < this->columns && f.row < this->rows)
	{
		f.state = this->ppFields[f.row][f.column];
		if(f.state != BOXSTATE_NOTEXISTENT)
		{
			surroundingBoxes.Push(f);
		}
	}
}

bool MineSweeperBot::Guess()
{
	MineSweeperInterface &msi = MineSweeperInterface::GetInstance();

	repeat(this->rows, row)
	{
		repeat(this->columns, column)
		{
			if(this->ppFields[row][column] == BOXSTATE_UNREVEALED)
			{
				LOGINFO("Guessing [" + CString(column) + "|" + CString(row) + "]");
				msi.MoveMouseOnField(column, row);
				msi.Reveal(column, row);
				return true;
			}
		}
	}
	return false;
}

void MineSweeperBot::UpdateFields()
{
	repeat(this->rows, row)
	{
		repeat(this->columns, column)
		{
			if(this->ppFields[row][column] == BOXSTATE_UNREVEALED)
			{
				this->ppFields[row][column] = MineSweeperInterface::GetInstance().GetBoxState(column, row);
			}
		}
	}
	//LOGFIELD();
}

//Public Functions
void MineSweeperBot::ClearFields()
{
	if(this->ppFields)
	{
		repeat(this->rows, row)
		{
			repeat(this->columns, column)
			{
				this->ppFields[row][column] = BOXSTATE_UNREVEALED;
			}
		}
	}
}

MineSweeperBot &MineSweeperBot::GetInstance()
{
	static MineSweeperBot bot;
	return bot;
}

void MineSweeperBot::Init()
{
	MineSweeperInterface &msi = MineSweeperInterface::GetInstance();

	this->rows = msi.GetNoOfRows();
	this->columns = msi.GetNoOfColumns();
	this->maxMoves = this->rows * this->columns;
	this->ppFields = new EBoxState*[this->rows];

	repeat(this->rows, row)
	{
		this->ppFields[row] = new EBoxState[this->columns];
		repeat(this->columns, column)
		{
			this->ppFields[row][column] = BOXSTATE_UNREVEALED;
		}
	}
	this->UpdateFields();
	this->isInitiated = true;
}

bool MineSweeperBot::IsInitiated()
{
	return this->isInitiated;
}

void MineSweeperBot::Release()
{
	if(this->ppFields)
	{
		repeat(this->rows, i)
		{
			delete[] this->ppFields[i];
		}
		delete[] this->ppFields;
		this->ppFields = NULL;
	}
	
	this->isInitiated = false;
}

void MineSweeperBot::SetGuess(bool guess)
{
	this->guess = guess;
}

bool MineSweeperBot::Step()
{
	MineSweeperInterface &msi = MineSweeperInterface::GetInstance();

	this->UpdateFields();
	repeat(this->rows, row)
	{
		repeat(this->columns, column)
		{
			if(this->ppFields[row][column] == BOXSTATE_MINE)
			{
				LOGINFO("Damn... bot lost the game");
				LOGFIELD();
				this->Release();
				msi.Release();
				return false;
			}
		}
	}

	if(!this->DoMove())
	{
		if(this->guess)
		{
			if(!this->Guess())
			{
				LOGINFO("Bot won the game :)");
				this->EnterName();
				this->Release();
				msi.Release();
				
				return false;
			}
		}
		else
		{
			repeat(this->rows, row)
			{
				repeat(this->columns, column)
				{
					if(this->ppFields[row][column] == BOXSTATE_UNREVEALED)
					{
						LOGINFO("No move could be made.");
						this->ClearFields();

						return false;
					}
				}
			}
			LOGINFO("Bot won the game :)");
			this->EnterName();
			this->Release();
			msi.Release();
			
			return false;
		}
	}

	return true;
}
*/