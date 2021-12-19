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
//Class Header
#include "MineSweeperBot.hpp"

//Constructor
MineSweeperBot::MineSweeperBot(UniquePointer<MineSweeperInterface> &&msInterface, Log &log) : msInterface(Move(msInterface)), log(log),
	fields(this->msInterface->GetNumberOfRows(), this->msInterface->GetNumberOfColumns())
{
	this->guess = false;
	this->UpdateFields();
}

//Public methods
bool MineSweeperBot::CanContinue()
{
	for (uint32 row = 0; row < this->fields.GetNumberOfRows(); row++)
	{
		for (uint32 col = 0; col < this->fields.GetNumberOfColumns(); col++)
		{
			if (this->fields(row, col) == BoxState::Mine)
			{
				LOG_INFO(u8"Damn... bot lost the game");
				this->LogField();
				return false;
			}
		}
	}

	return true;
}

void MineSweeperBot::LogField()
{
	String fieldString;

	for (uint32 row = 0; row < this->fields.GetNumberOfRows(); row++)
	{
		fieldString += u8"|";
		for (uint32 col = 0; col < this->fields.GetNumberOfColumns(); col++)
		{
			switch (this->fields(row, col))
			{
			case BoxState::Unrevealed:
				fieldString += u8"?";
				break;
			case BoxState::Mine:
				fieldString += u8"X";
				break;
			case BoxState::NearbyMines2:
				fieldString += u8"2";
				break;
			case BoxState::NearbyMines4:
				fieldString += u8"4";
				break;
			/*case BOXSTATE_EMPTY:
				CLog::WriteString(" ");
				break;
			case BOXSTATE_DEFUSED:
				CLog::WriteString("!");
				break;
			case BOXSTATE_WRONGMINE:
				CLog::WriteString("#");
				break;
			case BOXSTATE_1NEARBYBOMB:
				CLog::WriteString("1");
				break;
			case BOXSTATE_3NEARBYBOMBS:
				CLog::WriteString("3");
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
				break;*/
			}
			fieldString += u8"|";
		}
		fieldString += u8"\r\n";
	}

	this->log.Field(fieldString);
}

void MineSweeperBot::Step()
{
	bool didMove = false;
	this->UpdateFields();

	if (this->CanContinue())
	{
		if (this->DoMove()) //try to do a move
		{
			didMove = true;
		}
		else
		{
			if (this->guess)
			{
				if (this->Guess())
					didMove = true;
				else
					NOT_IMPLEMENTED_ERROR; //todo: bot won the came i think
			}
			else
			{
				LOG_INFO(u8"No move could be made without needing to guess.");
			}
		}
	}
	else
	{
		LOG_INFO(u8"No move could be made.");
	}

	if (didMove)
	{
		this->UpdateFields();
		this->LogField();
	}
}

//Private methods
bool MineSweeperBot::DoMove()
{
	for (uint32 row = 0; row < this->fields.GetNumberOfRows(); row++)
	{
		for (uint32 col = 0; col < this->fields.GetNumberOfColumns(); col++)
		{
			uint8 nearbyMines = this->GetNumberOfNearbyMines(this->fields(row, col));
			if (nearbyMines == Unsigned<uint8>::Max()) //don't know
				continue;
			DynamicArray<Field> surroundingBoxes = this->GetSurroundingBoxes(col, row);

			uint8 unrevealedBoxCount = 0;
			uint8 defusedBoxCount = 0;
			for(const Field &f : surroundingBoxes)
			{
				if (f.state == BoxState::Unrevealed)
					unrevealedBoxCount++;
				if (f.state == BoxState::Defused)
					defusedBoxCount++;
			}
			uint8 resultingNearbyMines = nearbyMines - defusedBoxCount;
			
			if (resultingNearbyMines == 0) //all nearby mines have been defused... reveal all unrevealed boxes
			{
				for (const Field &f : surroundingBoxes)
				{
					if (f.state == BoxState::Unrevealed)
					{
						LOG_INFO(u8"Revealing [" + String::Number(f.column) + u8"|" + String::Number(f.row) + u8"]");
						this->msInterface->Reveal(f.column, f.row);
						return true; //successfull move
					}
				}
			}
			if (unrevealedBoxCount == resultingNearbyMines) //same amount of unrevealed boxes and nearby mines... AND ... there are less defused fields than nearby mines
			{
				for (const Field &f : surroundingBoxes)
				{
					if (f.state == BoxState::Unrevealed)
					{
						LOG_INFO(u8"Defusing [" + String::Number(f.column) + "|" + String::Number(f.row) + u8"]");
						this->msInterface->Defuse(f.column, f.row);
						return true; //successfull move
					}
				}
			}
		}
	}

	return false;
}

uint8 MineSweeperBot::GetNumberOfNearbyMines(BoxState state)
{
	switch (state)
	{
	case BoxState ::NearbyMines2:
		return 2;
	/*case BOXSTATE_1NEARBYBOMB:
		nearbyMines = 1;
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
		break;*/
	case BoxState::Defused:
	case BoxState::Mine:
	case BoxState::Unrevealed:
		return Unsigned<uint8>::Max();
	}

	return 0;
}

DynamicArray<Field> MineSweeperBot::GetSurroundingBoxes(uint16 column, uint16 row)
{
	DynamicArray<Field> result;
	result.EnsureCapacity(8); //max number of surrounding boxes is 8
	uint16 r = row - 1;
	if (row == 0)
		r = 0;
	uint16 c = column - 1;
	if (column == 0)
		c = 0;

	for (; r <= row + 1; r++)
	{
		if (r >= this->msInterface->GetNumberOfRows())
			break; //out of bounds
		for (; c <= column + 1; c++)
		{
			if (c >= this->msInterface->GetNumberOfColumns())
				break; //out of bounds
			if (r == row && c == column)
				continue; //skip the field itself

			Field f;
			f.column = c;
			f.row = r;
			f.state = this->fields(r, c);
			result.Push(f);
		}
	}

	return result;
}

bool MineSweeperBot::Guess()
{
	FixedTable<float64> mineLikelihood(this->fields.GetNumberOfRows(), this->fields.GetNumberOfColumns());

	//compute likelihood
	for (uint32 row = 0; row < this->fields.GetNumberOfRows(); row++)
	{
		for (uint32 col = 0; col < this->fields.GetNumberOfColumns(); col++)
		{
			if (this->fields(row, col) == BoxState::Unrevealed)
			{
				DynamicArray<Field> surroundingBoxes = this->GetSurroundingBoxes(col, row);
				uint8 nPotentialMines = 0;

				for (const Field &f : surroundingBoxes)
				{
					switch (f.state)
					{
					case BoxState::Defused:
						break; //not of interest
					case BoxState::Unrevealed:
						nPotentialMines++; //we need to assume that its a mine
						break;
					}
				}

				mineLikelihood(row, col) = nPotentialMines / float64(surroundingBoxes.GetNumberOfElements());
			}
			else
			{
				mineLikelihood(row, col) = 2;
			}
		}
	}

	LOG_INFO(u8"Finding best guess box");
	this->LogLikelihoodField(mineLikelihood);

	uint16 bestCol = 0, bestRow = 0;
	float64 best = mineLikelihood(0, 0);
	for (uint32 row = 0; row < this->fields.GetNumberOfRows(); row++)
	{
		for (uint32 col = 0; col < this->fields.GetNumberOfColumns(); col++)
		{
			if(mineLikelihood(row, col) < best)
			{
				best = mineLikelihood(row, col);
				bestCol = col;
				bestRow = row;
			}
		}
	}

	LOG_INFO(u8"Guessing [" + String::Number(bestCol) + u8"|" + String::Number(bestRow) + u8"]");
	this->msInterface->Reveal(bestCol, bestRow);

	return true;
}

void MineSweeperBot::LogLikelihoodField(const FixedTable<float64> &likelihoods)
{
	String fieldString;
	
	for (uint32 row = 0; row < likelihoods.GetNumberOfRows(); row++)
	{
		fieldString += u8"|";
		for (uint32 col = 0; col < likelihoods.GetNumberOfColumns(); col++)
		{
			if (likelihoods(row, col) == 2)
				fieldString += u8"    ";
			else
				fieldString += String::Number(likelihoods(row, col), FloatDisplayMode::FixedPointNotation, 3);
			fieldString += u8"|";
		}
		fieldString += u8"\r\n";
	}
	
	this->log.Field(fieldString);
}

void MineSweeperBot::UpdateFields()
{
	for (uint32 row = 0; row < this->fields.GetNumberOfRows(); row++)
		for (uint32 col = 0; col < this->fields.GetNumberOfColumns(); col++)
			this->fields(row, col) = this->msInterface->GetBoxState(row, col);
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

bool MineSweeperBot::Guess()
{
	MineSweeperInterface &msi = MineSweeperInterface::GetInstance();

	repeat(this->rows, row)
	{
		repeat(this->columns, column)
		{
			if(this->ppFields[row][column] == BOXSTATE_UNREVEALED)
			{
				msi.MoveMouseOnField(column, row);
				msi.Reveal(column, row);
				return true;
			}
		}
	}
	return false;
}

//Public Functions
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
*/

/*
LOGINFO("Bot won the game :)");
this->EnterName();
this->Release();
msi.Release();
*/