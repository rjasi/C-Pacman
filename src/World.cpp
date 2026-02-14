#include "World.h"

#include <iostream>

namespace Pacman
{
    World::World() 
    :
    blinkyTargetStrategy_(BLINKY_SCATTER_CORNER),
    pinkyTargetStrategy_({PINKY_SCATTER_CORNER}),
    inkyTargetStrategy_({INKY_SCATTER_CORNER}),
    clydeTargetStrategy_({CLYDE_SCATTER_CORNER}),
    blinky_(blinkyTargetStrategy_, greedyManhattanPathingStrategy_),
    pinky_(pinkyTargetStrategy_, greedyManhattanPathingStrategy_),
    inky_(inkyTargetStrategy_, greedyManhattanPathingStrategy_),
    clyde_(clydeTargetStrategy_, greedyManhattanPathingStrategy_)
    {
        pacmanEntity_.setPosition(maze_.tileToWorld(TileRC{1, 1}));

        // TileRC x = Maze::INFRONT_DOOR;
        // std::cerr << "c : " << x.c << " r : " << x.r << "\n";

        blinky_.setPosition(maze_.tileToWorldOnBoundary(Maze::INFRONT_DOOR));
        blinky_.setState(GhostState::Chase);
        blinky_.setDirection(Dir::Left);
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

        TargetContext ctx
        {
            .pacman_tile = maze_.worldToTile(pacmanEntity_.position()),
            .pacman_dir = pacmanEntity_.direction(),
            .blinky_tile = maze_.worldToTile(blinky_.position()),
            .clyde_tile = maze_.worldToTile(clyde_.position())
        };

        blinky_.setTargetContext(ctx);
        blinky_.update(dt, maze_);

        pinky_.setTargetContext(ctx);
        pinky_.update(dt, maze_);

        inky_.setTargetContext(ctx);
        inky_.update(dt, maze_);

        clyde_.setTargetContext(ctx);
        clyde_.update(dt, maze_);

        
        blinkElapsed_ += dt;
        if (blinkElapsed_ >= blinkPeriod_) 
        {
            blinkElapsed_ -= blinkPeriod_;
            powerPelletVisible_ = !powerPelletVisible_;
        }

        if (maze_.tryEatPellet(pacmanEntity_.position()))
        {
            score_ += 10;
        }

        if (maze_.tryEatPowerPellet(pacmanEntity_.position()))
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