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
#pragma once
#include <StdXX.hpp>
using namespace StdXX;
using namespace StdXX::UI;

//Forward declarations
class MainWindow;

class Log
{
public:
	//Methods
	void Error(const String &msg, const char *filename, const char *functionname, int lineno);
	void Field(const String &fieldString);
	String GetField(uint32 index) const;
	void Warning(const String &msg, const char *filename, const char *functionname, int lineno);

	//Inline
	inline const DynamicArray<String> &GetLines() const
	{
		return this->logLines;
	}

	inline String GetNewestField() const
	{
		if (this->logFields.IsEmpty())
			return String();
		auto it = this->logFields.end();
		--it;
		return (*it).value;
	}

private:
	//Members
	BinaryTreeMap<uint32, String> logFields;

	//Methods
	void WriteString(const String &msg);
};