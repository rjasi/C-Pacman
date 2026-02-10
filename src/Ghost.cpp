#include "Ghost.h"
#include "PathQuery.h"

#include <iostream>

namespace Pacman
{

    //todo remove this. temporary while not all IGhostTargetStrategy types are implemented yet
    Ghost::Ghost()
    {
        speed_ = 20.0f;
    }

    Ghost::Ghost(const IGhostTargetStrategy& ghostTargetStrategy, const IPathingStrategy& pathingStrategy)
    : ghostTargetStrategy_(&ghostTargetStrategy),
    pathingStrategy_(&pathingStrategy)
    {
        speed_ = 50.0f;
    }

    void Ghost::setState(GhostState state)
    {
        state_ = state;
    }

    GhostState Ghost::state() const
    {
        return state_;
    }

    void Ghost::update(sf::Time dt, const Maze& maze)
    {
        switch (state_)
        {
            case GhostState::InHouse:
                paceInHouse(dt, maze);
                break;
            case GhostState::GettingToHouseCenter:
                moveToDoor(dt, maze);
                break;
            case GhostState::LeavingHouse:
                moveToInfrontOfDoor(dt, maze);
                break;
            case GhostState::Active:
                active(dt, maze);
                move(dt);
                warp();
                break;
            case GhostState::EatenReturning:
                break;
            case GhostState::Frightened:
                break;

        }

        
    }

    void Ghost::paceInHouse(sf::Time dt, const Maze& maze)
    {
        speed_ = 20.f;
        // todo refactor when ghost changes state and send back into house
        if (current_ == Dir::Left || current_ == Dir::Right)
        {
            current_ = Dir::Up;
        }

        // sf::Vector2f step = DirUtils::dirVecWorld(current_) * (speed_ * dt.asSeconds());
        // sf::Vector2f nextPos = pos_ + step;

        // when pacing, go up or down till wall then reverse direction
        // note: maze.nearTileCenter(pos_)  won't work because ghosts are 
        // aligned at tile boundary on x axis when pacing in the house

        // todo maybe clamp to x boundary? 

        if (!maze.canEnterNextTile(current_, pos_))
        {
            // pos_ = maze.tileCenterClampX(maze.worldToTile(pos_));
            current_ = current_ == Dir::Down ? Dir::Up : Dir::Down;
        }

        move(dt);
    }

    void Ghost::moveToDoor(sf::Time dt, const Maze& maze)
    {
        speed_ = 20.f;
        sf::Vector2f target = maze.tileToWorldOnBoundary(Maze::HOUSE_CENTER);

        // first center y and clamp if close enougb
        if (std::abs(pos_.y - target.y) <= Maze::CENTER_EPS)
        {
            pos_.y = target.y;
            moveToExit(dt, maze);
        } 
        else if (pos_.y < target.y)
        {
            current_ = Dir::Down;
            //move down
            move(dt);
        }
        else if (pos_.y > target.y)
        {
            current_ = Dir::Up;
            // move up
            move(dt);
        }

    }

    void Ghost::moveToExit(sf::Time dt, const Maze& maze)
    {
        speed_ = 20.f;
        sf::Vector2f target = maze.tileToWorldOnBoundary(Maze::HOUSE_CENTER);

        if (std::abs(pos_.x - target.x) <= Maze::CENTER_EPS)
        {
            pos_.x = target.x;
            state_ = GhostState::LeavingHouse;
            moveToInfrontOfDoor(dt, maze);
        } 
        else if (pos_.x < target.x)
        {
            current_ = Dir::Right;
            move(dt);
        }
        else if (pos_.x > target.x)
        {
            current_ = Dir::Left;
            move(dt);
        }
    }

    void Ghost::moveToInfrontOfDoor(sf::Time dt, const Maze& maze)
    {
        sf::Vector2f target = maze.tileToWorldOnBoundary(Maze::INFRONT_DOOR);

        // guranteed to be alinged on x from moveToExit so no need to check y 
        // first center y and clamp if close enougb
        if (std::abs(pos_.y - target.y) <= Maze::CENTER_EPS)
        {
            pos_.y = target.y;
            current_ = Dir::Left; //todo randomly choose left or right
            state_ = GhostState::Active;
        } 
        else if (pos_.y < target.y)
        {
            current_ = Dir::Down;
            //move down
            move(dt);
        }
        else if (pos_.y > target.y)
        {
            current_ = Dir::Up;
            // move up
            move(dt);
        }
    }

    // determine where to go
    void Ghost::active(sf::Time dt, const Maze& maze)
    {
        speed_ = 50.f;
        // only choose direction at tile center
        if (maze.nearTileCenter(pos_, centerEps())) 
        {
            pos_ = maze.tileCenter(pos_);
        }
        else
        {
            return;
        }

        if (isWarping(current_, pos_, maze))
        {
            return;
        }

        if (ghostTargetStrategy_ == nullptr || pathingStrategy_ == nullptr || targetContext_ == nullptr)
        {
            return;
        }

        TileRC target = ghostTargetStrategy_->getTarget(*targetContext_);

        PathQuery query = 
        {
            .current_tile = maze.worldToTile(pos_),
            .current_direction = current_,
            .target_tile = target,
            .canReverse = false
        };

        current_ = pathingStrategy_->chooseNext(maze, query);
        
        targetContext_ =  nullptr; // reset
    }

    void Ghost::setTargetContext(const TargetContext& ctx)
    {
        targetContext_ = &ctx;
    }

    float Ghost::centerEps() const
    {
        return 0.30f; // MAKE SURE THIS IS < dirVec(current_) * (speed_ * dt.asSeconds())
        // issue: 
        // pos at 1.0, move 0.24, get 1.24 
        // if eps is 0.25, it wil snap to center of current tile so you never move
        // setting too small will cause to almost never center if the speed is too high
    }



}