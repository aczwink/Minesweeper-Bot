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
#include "MainWindow.hpp"

class MainWindowLogger : public MovesLogger
{
public:
    //Constructor
    inline MainWindowLogger(MainWindow& mainWindow, MineSweeperInterface& mineSweeperInterface)
        : mainWindow(mainWindow), mineSweeperInterface(mineSweeperInterface)
    {
    }

    //Methods
    String GetField(uint32 lineNumber) const override;
    String GetLine(uint32 lineNumber) const override;
    uint32 GetNumberOfLines() const override;
    void Info(const String &text) override;

private:
    //Members
    MainWindow& mainWindow;
    MineSweeperInterface& mineSweeperInterface;
    DynamicArray<String> logLines;
    DynamicArray<String> logFields;

    //Inline
    inline String GetTime() const
    {
        DateTime t = DateTime::Now();
        return TimeZone::GetUserLocalTimeZone().Translate(t).ToISOString();
    }
};