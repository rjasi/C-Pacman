#pragma once

#include "MoveableEntity.h"
#include "GhostState.h"
#include "IGhostTargetStrategy.h"

namespace Pacman
{
    class Ghost : public MoveableEntity
    {
        private:
            GhostState state_ = GhostState::InHouse;
            const IGhostTargetStrategy* ghostTargetStrategy_;

            void paceInHouse(sf::Time dt, const Maze& maze);
            void active(sf::Time dt, const Maze& maze);

            // scripted logic for exiting house
            // 1. align ghost on y axis with house center
            // 2. then align on x axis with house center
            // 3. then move to INFRONT_HOUSE
            // 4. done
            // todo: split the states, doing too much 
            void moveToDoor(sf::Time dt, const Maze& maze);
            void moveToExit(sf::Time dt, const Maze& maze);
            void moveToInfrontOfDoor(sf::Time dt, const Maze& maze);

            void move(sf::Time dt);

        public:
            Ghost();
            Ghost(const Ghost& ghost) = delete;
            Ghost& operator=(const Ghost& ghost) = delete;
            
            explicit Ghost(IGhostTargetStrategy& ghostTargetStrategy);
            void update(sf::Time dt, const Maze& maze) override;
            void setState(GhostState state);
            GhostState state() const;

    };
}