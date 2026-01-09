#include "World.h"

namespace Pacman
{
    World::World()
    {
        pacmanEntity_.setPosition(maze_.tileToWorld(1,1));
    }

    void World::setPlayerRequestedDir(Dir d)
    {
        pacmanEntity_.requestDirection(d);
    }

    void World::update(sf::Time dt)
    {
        pacmanEntity_.update(dt, maze_);

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
}