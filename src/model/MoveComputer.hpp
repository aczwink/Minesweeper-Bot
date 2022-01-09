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
#include "BoardState.hpp"
#include "GameMove.hpp"

class MoveComputer
{
public:
    //Methods
    GameMove ComputeBestMove(const BoardState& boardState, bool& wasGuess) const;
    /**
     * The likelihood that a box contains a mine.
     */
    FixedTable<float64> ComputeMineLikelihood(const BoardState& boardState) const;

    //Inline
    inline GameMove ComputeBestMove(const BoardState& boardState) const
    {
        bool wasGuess;
        return this->ComputeBestMove(boardState, wasGuess);
    }

private:
    //Methods
    GameMove ComputeBestMoveByGuessing(const BoardState& boardState) const;
    Optional<GameMove> ComputeBestMoveWithoutGuessing(const BoardState& boardState) const;
    uint8 GetNumberOfNearbyMines(BoxState state) const;
};