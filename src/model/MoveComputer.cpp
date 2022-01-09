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
#include "MoveComputer.hpp"

//Public methods
GameMove MoveComputer::ComputeBestMove(const BoardState &boardState, bool& wasGuess) const
{
    auto move = this->ComputeBestMoveWithoutGuessing(boardState);
    if(move.HasValue())
    {
        wasGuess = false;
        return *move;
    }

    wasGuess = true;
    return this->ComputeBestMoveByGuessing(boardState);
}

FixedTable<float64> MoveComputer::ComputeMineLikelihood(const BoardState &boardState) const
{
    FixedTable<float64> mineLikelihood(boardState.NumberOfRows(), boardState.NumberOfColumns());

    //compute likelihood
    for (uint16 row = 0; row < boardState.NumberOfRows(); row++)
    {
        for (uint16 col = 0; col < boardState.NumberOfColumns(); col++)
        {
            if (boardState.GetState(row, col) == BoxState::Unrevealed)
            {
                DynamicArray<IndexedField> surroundingBoxes = boardState.CollectSurroundingBoxes(row, col);
                uint8 nPotentialMines = 0;

                for (const IndexedField &f : surroundingBoxes)
                {
                    switch (f.boxState)
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

    return mineLikelihood;
}

//Private methods
GameMove MoveComputer::ComputeBestMoveByGuessing(const BoardState &boardState) const
{
    auto mineLikelihood = this->ComputeMineLikelihood(boardState);

    uint16 bestCol = 0, bestRow = 0;
    float64 best = mineLikelihood(0, 0);
    for (uint16 row = 0; row < boardState.NumberOfRows(); row++)
    {
        for (uint16 col = 0; col < boardState.NumberOfColumns(); col++)
        {
            if(mineLikelihood(row, col) < best)
            {
                best = mineLikelihood(row, col);
                bestCol = col;
                bestRow = row;
            }
        }
    }

    GameMove gameMove;
    gameMove.type = GameMoveType::Reveal;
    gameMove.row = bestRow;
    gameMove.column = bestCol;

    return gameMove;
}

Optional<GameMove> MoveComputer::ComputeBestMoveWithoutGuessing(const BoardState &boardState) const
{
    for (uint16 row = 0; row < boardState.NumberOfRows(); row++)
    {
        for (uint16 col = 0; col < boardState.NumberOfColumns(); col++)
        {
            uint8 nearbyMines = this->GetNumberOfNearbyMines(boardState.GetState(row, col));
            if (nearbyMines == Unsigned<uint8>::Max()) //don't know
                continue;

            DynamicArray<IndexedField> surroundingBoxes = boardState.CollectSurroundingBoxes(row, col);
            uint8 unrevealedBoxCount = 0;
            uint8 defusedBoxCount = 0;
            for(const IndexedField &f : surroundingBoxes)
            {
                if (f.boxState == BoxState::Unrevealed)
                    unrevealedBoxCount++;
                if (f.boxState == BoxState::Defused)
                    defusedBoxCount++;
            }
            uint8 resultingNearbyMines = nearbyMines - defusedBoxCount;

            if (resultingNearbyMines == 0) //all nearby mines have been defused... reveal all unrevealed boxes
            {
                for (const IndexedField &f : surroundingBoxes)
                {
                    if (f.boxState == BoxState::Unrevealed)
                    {
                        GameMove gameMove;
                        gameMove.column = f.column;
                        gameMove.row = f.row;
                        gameMove.type = GameMoveType::Reveal;
                        return gameMove;
                    }
                }
            }
            if (unrevealedBoxCount == resultingNearbyMines) //same amount of unrevealed boxes and nearby mines... AND ... there are less defused fields than nearby mines
            {
                for (const IndexedField &f : surroundingBoxes)
                {
                    if (f.boxState == BoxState::Unrevealed)
                    {
                        GameMove gameMove;
                        gameMove.column = f.column;
                        gameMove.row = f.row;
                        gameMove.type = GameMoveType::Defuse;
                        return gameMove;
                    }
                }
            }
        }
    }

    return Optional<GameMove>();
}

uint8 MoveComputer::GetNumberOfNearbyMines(BoxState state) const
{
    switch (state)
    {
        case BoxState::NearbyMines1:
            return 1;
        case BoxState::NearbyMines2:
            return 2;
        case BoxState::NearbyMines3:
            return 3;
        case BoxState::NearbyMines4:
            return 4;
            /*
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