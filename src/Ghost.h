#pragma once

#include "MoveableEntity.h"

namespace Pacman
{
    enum class GhostState 
    { 
        InHouse, 
        LeavingHouse,
        GettingToHouseCenter,
        Active, 
        Frightened, 
        EatenReturning 
    };

    class Ghost : public MoveableEntity
    {
        private:
            GhostState state_ = GhostState::InHouse;
            void paceInHouse(sf::Time dt, const Maze& maze);

            // logic for exiting house
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
            void update(sf::Time dt, const Maze& maze) override;
            void setState(GhostState state);


    };
}