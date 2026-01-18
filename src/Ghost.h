#pragma once

#include "MoveableEntity.h"

namespace Pacman
{
    enum class GhostState 
    { 
        InHouse, 
        LeavingHouse, 
        Active, 
        Frightened, 
        EatenReturning 
    };

    class Ghost : public MoveableEntity
    {
        private:
            GhostState state_ = GhostState::InHouse;
            void paceInHouse(sf::Time dt, const Maze& maze);

        public:
            Ghost();
            void update(sf::Time dt, const Maze& maze) override;
            void setState(GhostState state);

    };
}