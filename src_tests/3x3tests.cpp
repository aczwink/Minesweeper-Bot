/*
 * Copyright (c) 2021 Amir Czwink (amir130@hotmail.de)
 *
 * This file is part of ACBackup.
 *
 * ACBackup is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ACBackup is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ACBackup.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <StdXXTest.hpp>
//Local
#include "BoardBuilder.hpp"
#include "../src/model/MoveComputer.hpp"

using namespace StdXX;

TEST_SUITE(Tests3x3)
{
    TEST_CASE(SimpleTest)
    {
        BoardBuilder builder(3, 3);
        builder.SetMine(2, 2);
        builder.SetRevealed(0, 0);

        MineSweeperInterface& interface = builder.Interface();
        auto board = interface.QueryState();

        stdOut << board.ToString() << endl;

        MoveComputer bot;
        auto move = bot.ComputeBestMove(board);

        ASSERT_EQUALS(2, move.column);
        ASSERT_EQUALS(2, move.row);
        ASSERT_EQUALS(GameMoveType::Defuse, move.type);
    }
};