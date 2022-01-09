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
//Class header
#include "MineSweeperBot.hpp"
//Local
#include "MoveComputer.hpp"

//Public methods
void MineSweeperBot::Step()
{
    auto state = this->mineSweeperInterface.QueryState();
    switch(state.ComputePlayingState())
    {
        case PlayingState::Active:
            this->DoMove(state);
            break;
        case PlayingState::Won:
            this->logger.Info(u8"Game is already won");
            break;
        case PlayingState::Lost:
            this->logger.Info(u8"Game is already lost");
            break;
    }
}

//Private methods
void MineSweeperBot::DoMove(const BoardState& boardState)
{
    MoveComputer moveComputer;
    bool wasGuess;
    auto move = moveComputer.ComputeBestMove(boardState, wasGuess);

    if(wasGuess and !this->guess)
    {
        this->logger.Info(u8"No move could be made without needing to guess.");
    }
    else
    {
        this->mineSweeperInterface.DoMove(move);
        if(wasGuess)
            this->logger.Info(u8"Guessing [" + String::Number(move.column) + u8"|" + String::Number(move.row) + u8"]");
        else
        {
            if (move.type == GameMoveType::Reveal)
                this->logger.Info(u8"Revealing [" + String::Number(move.column) + u8"|" + String::Number(move.row) + u8"]");
            else
                this->logger.Info(u8"Defusing [" + String::Number(move.column) + "|" + String::Number(move.row) + u8"]");
        }

        switch(this->mineSweeperInterface.QueryState().ComputePlayingState())
        {
            case PlayingState::Lost:
                this->logger.Info(u8"Damn... bot lost the game");
                break;
            case PlayingState::Won:
                this->logger.Info(u8"Bot won the game :)");
                break;
        }
    }
}