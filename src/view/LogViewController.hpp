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
//Local
#include "../model/MovesLogger.hpp"
using namespace StdXX::UI;

class LogViewController : public ListController
{
public:
    //Constructor
    inline LogViewController(const MovesLogger& logger) : logger(logger)
    {
    }

    //Methods
    uint32 GetNumberOfItems() const override;
    String GetText(uint32 index) const override;

    //Inline
    inline ControllerIndex GetNewestLineIndex() const
    {
        return this->GetChildIndex(this->GetNumberOfItems() - 1, Unsigned<uint32>::Max(), {});
    }

private:
    //Members
    const MovesLogger& logger;
};