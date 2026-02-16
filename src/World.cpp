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
    blinky_(blinkyTargetStrategy_, greedyManhattanPathingStrategy_, GameCharacters::Blinky, Maze::HOUSE_CENTER),
    pinky_(pinkyTargetStrategy_, greedyManhattanPathingStrategy_, GameCharacters::Pinky, Maze::HOUSE_CENTER),
    inky_(inkyTargetStrategy_, greedyManhattanPathingStrategy_, GameCharacters::Inky, Maze::HOUSE_LEFT),
    clyde_(clydeTargetStrategy_, greedyManhattanPathingStrategy_, GameCharacters::Clyde, Maze::HOUSE_RIGHT),
    ghostDirector_(cfg_)
    {
        pacmanEntity_.setPosition(maze_.tileToWorld(TileRC{1, 1}));

        blinky_.setPosition(maze_.tileToWorldOnBoundary(Maze::INFRONT_DOOR_LEFT));
        blinky_.setState(GhostState::Chase);
        blinky_.setHouseState(HouseState::Outside);
        blinky_.setDirection(Dir::Left);

        pinky_.setPosition(maze_.tileToWorldOnBoundary(Maze::HOUSE_CENTER));
        pinky_.setDirection(Dir::Down);
        pinky_.setHouseState(HouseState::InHouse);
        
        inky_.setPosition(maze_.tileToWorldOnBoundary(Maze::HOUSE_LEFT));
        inky_.setDirection(Dir::Up);
        inky_.setHouseState(HouseState::InHouse);

        clyde_.setPosition(maze_.tileToWorldOnBoundary(Maze::HOUSE_RIGHT));
        clyde_.setDirection(Dir::Up);
        clyde_.setHouseState(HouseState::InHouse);
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
        advanceBlinkTimer(dt);

        auto pos = maze_.tileToWorld(Maze::INFRONT_DOOR_LEFT);
        popups_.push_back({pos, "ABC DEF", sf::seconds(5.0f), TextColors::WHITE});

        switch (state_)
        {
            case WorldState::Playing:
                playing(dt);
            case WorldState::GhostEaten:
                ghostEaten(dt);
            case WorldState::Died:
            case WorldState::LevelCleared:
                return;
            default:
                return;
        }
    }

    void World::ghostEaten(sf::Time dt)
    {
        eatenTimer_ += dt;
        if (eatenTimer_ >= EATEN_PAUSE)
        {
            state_ = WorldState::Playing;
            eatenGhost = nullptr;
            eatenTimer_ = sf::Time{};
        }
    }

    void World::advanceBlinkTimer(sf::Time dt)
    {
        blinkElapsed_ += dt;
        if (blinkElapsed_ >= blinkPeriod_) 
        {
            blinkElapsed_ -= blinkPeriod_;
            powerPelletVisible_ = !powerPelletVisible_;
        }
    }

    void World::playing(sf::Time dt)
    {

        pacmanEntity_.update(dt, maze_);

        if (maze_.tryEatPellet(pacmanEntity_.position()))
        {
            score_ += 10;
            ghostDirector_.pelletEaten();
        }

        if (maze_.tryEatPowerPellet(pacmanEntity_.position()))
        {
            score_ += 50;
            ghostDirector_.powerPelletEaten();
        }

        TargetContext ctx
        {
            .pacman_tile = maze_.worldToTile(pacmanEntity_.position()),
            .pacman_dir = pacmanEntity_.direction(),
            .blinky_tile = maze_.worldToTile(blinky_.position()),
            .clyde_tile = maze_.worldToTile(clyde_.position())
        };

        ghostDirector_.update({&blinky_, &pinky_, &inky_, &clyde_}, maze_, ctx, dt);
        // resolveCollision();
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

    void World::resolveCollision()
    {
        TileRC pacmanTile = maze_.worldToTile(pacmanEntity_.position());

        for (Ghost& ghost : { std::ref(blinky_), std::ref(pinky_),
                      std::ref(inky_), std::ref(clyde_) })
        {
            TileRC ghostTile = maze_.worldToTile(ghost.position());

            // todo check if frightened or actives
            if (pacmanTile == ghostTile)
            {
                state_ = WorldState::GhostEaten;
                eatenGhost = &ghost;
                eatenTimer_ = sf::Time{};
                return;
            }

            state_ = WorldState::Playing;
            eatenGhost = nullptr;
        }
    }

    WorldState World::state() const
    {
        return state_;
    }

    const std::vector<Popup>& World::popups() const
    {
        return popups_;
    }
    
    void World::updatePopups(sf::Time dt)
    {
        for (auto it = popups_.begin(); it != popups_.end(); )
        {
            it->durationRemaining -= dt;
            if (it->durationRemaining <= sf::Time::Zero)
            {
                it = popups_.erase(it); 
            }
            else
            {
                ++it;
            }
        }
    }



}