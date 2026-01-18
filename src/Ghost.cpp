#include "Ghost.h"

#include <iostream>

namespace Pacman
{
    Ghost::Ghost()
    {
        speed_ = 20.0f;
    }

    void Ghost::setState(GhostState state)
    {
        state_ = state;
    }

    void Ghost::update(sf::Time dt, const Maze& maze)
    {
        switch (state_)
        {
            case GhostState::InHouse:
                paceInHouse(dt, maze);
                break;
            case GhostState::LeavingHouse:
                break;
            case GhostState::Active:
                break;
            case GhostState::EatenReturning:
                break;
            case GhostState::Frightened:
                break;

        }

        
    }

    void Ghost::paceInHouse(sf::Time dt, const Maze& maze)
    {
        // todo refactor when ghost changes state and send back into hous
        if (current_ == Dir::Left || current_ == Dir::Right)
        {
            current_ = Dir::Up;
        }

        sf::Vector2f step = dirVec(current_) * (speed_ * dt.asSeconds());
        sf::Vector2f nextPos = pos_ + step;

        // when pacing, go up or down till wall then reverse direction
        // note: maze.nearTileCenter(pos_)  won't work because ghosts are 
        // aligned at tile boundary on x axis when pacing in the house
        if (!canEnter(current_, nextPos, maze))
        {
            // todo maybe clamp to x boundary? 
            // pos_ = maze.tileCenterClampX(maze.worldToTile(pos_));
            current_ = current_ == Dir::Down ? Dir::Up : Dir::Down;
        }

        if (current_ != Dir::None) 
        {
            sf::Vector2f step = dirVec(current_) * (speed_ * dt.asSeconds());
            pos_ += step;
        }

    }
}