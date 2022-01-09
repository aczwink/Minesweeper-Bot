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

//Public methods
bool MineSweeperBot::Guess()
{
	LOG_INFO(u8"Finding best guess box");
	this->LogLikelihoodField(mineLikelihood);

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

/*
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
*/