#include "Ghost.h"

#include <iostream>

namespace Pacman
{
    Ghost::Ghost()
    {
        speed_ = 30.0f;
    }

    void Ghost::setState(GhostState state)
    {
        state_ = state;
    }

    void Ghost::update(sf::Time dt, const Maze& maze)
    {
        if (maze.nearTileCenter(pos_)) 
        {
            pos_ = maze.tileCenter(maze.worldToTile(pos_));

            // if (requested_ != Dir::None && canEnter(requested_, pos_, maze))
            //     current_ = requested_;

            // if (!canEnter(current_, pos_, maze))
            //     current_ = Dir::None;
        }
        if (state_ == GhostState::InHouse)
        {
            // todo refactor when ghost changes state and send back into hous
            if (current_ == Dir::Left || current_ == Dir::Right)
            {
                current_ = Dir::Up;
            }

            // when pacing, go up or down till wall then reverse direction
            if(!canEnter(current_, pos_, maze))
            {
                current_ = current_ == Dir::Down ? Dir::Up : Dir::Down;
            }
        }

        if (current_ != Dir::None) 
        {
            sf::Vector2f step = dirVec(current_) * (speed_ * dt.asSeconds());
            pos_ += step;
        }

    }
}