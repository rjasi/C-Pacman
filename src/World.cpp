#include "World.h"

#include <iostream>

namespace Pacman
{
    World::World() 
    :
    blinkyTargetStrategy_({1,1}),
    blinky_(blinkyTargetStrategy_)//,
    // pinky_(pinkyTargetStrategy_),
    // inky_(inkyTargetStrategy_),
    // clyde_(clydeTargetStrategy_)
    {
        pacmanEntity_.setPosition(maze_.tileToWorld(1,1));
        blinky_.setPosition(maze_.tileToWorldOnBoundary(Maze::INFRONT_DOOR));
        blinky_.setState(GhostState::Active);
        pinky_.setPosition(maze_.tileToWorldOnBoundary(Maze::HOUSE_CENTER));
        pinky_.setDirection(Dir::Down);
        inky_.setPosition(maze_.tileToWorldOnBoundary(Maze::HOUSE_LEFT));
        inky_.setDirection(Dir::Up);
        pinky_.setState(GhostState::GettingToHouseCenter);
        clyde_.setPosition(maze_.tileToWorldOnBoundary(Maze::HOUSE_RIGHT));
        clyde_.setDirection(Dir::Up);
    }

    void World::setPlayerRequestedDir(Dir d)
    {
        pacmanEntity_.requestDirection(d);
    }

    const MoveableEntity& World::pinky() const
    {
        return pinky_;
    }

    const MoveableEntity& World::inky() const
    {
        return inky_;
    }

    const MoveableEntity& World::clyde() const
    {
        return clyde_;
    }

    void World::update(sf::Time dt)
    {
        pacmanEntity_.update(dt, maze_);
        pinky_.update(dt, maze_);
        inky_.update(dt, maze_);
        clyde_.update(dt, maze_);

        blinkElapsed_ += dt;
        if (blinkElapsed_ >= blinkPeriod_) 
        {
            blinkElapsed_ -= blinkPeriod_;
            powerPelletVisible_ = !powerPelletVisible_;
        }

        sf::Vector2i tile = maze_.worldToTile(pacmanEntity_.position());

        if(maze_.tryEatPellet(tile.y, tile.x))
        {
            score_ += 10;
        }

        if(maze_.tryEatPowerPellet(tile.y, tile.x))
        {
            score_ += 60;
        }
    }

    const Maze& World::maze() const
    {
        return maze_;
    }

    const MoveableEntity& World::pacman() const
    {
        return pacmanEntity_;
    }

    bool World::powerPelletVisible() const
    {
        return powerPelletVisible_;
    }

    const MoveableEntity& World::blinky() const
    {
        return blinky_;
    }

}