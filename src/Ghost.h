#pragma once

#include "MoveableEntity.h"
#include "GhostState.h"
#include "GhostEnum.h"
#include "IGhostTargetStrategy.h"
#include "IPathingStrategy.h"
#include "TargetContext.h"

namespace Pacman
{
    class Ghost : public MoveableEntity
    {
        private:
            GameCharacters name_;
            bool flashFrightened_ = false;
            bool reverseRequested_ = false;
            GhostState state_ = GhostState::Chase;
            HouseState houseState_ = HouseState::InHouse;
            const IGhostTargetStrategy* ghostTargetStrategy_ = nullptr;
            const IPathingStrategy* pathingStrategy_ = nullptr;
            const TargetContext* targetContext_ = nullptr;

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

            float centerEps() const override;

        public:
            Ghost() = delete;
            Ghost(const Ghost& ghost) = delete;
            Ghost& operator=(const Ghost& ghost) = delete;
            explicit Ghost(
                const IGhostTargetStrategy& ghostTargetStrategy, 
                const IPathingStrategy& pathingStrategy,
                GameCharacters name);

            void update(sf::Time dt, const Maze& maze) override;
            void setState(GhostState state);
            void setHouseState(HouseState state);
            bool isOutsideHouse() const;
            void setTargetContext(const TargetContext& ctx);
            GhostState state() const;
            HouseState houseState() const;
            GameCharacters name() const;
            void requestReverseDirection();
            bool flashFrightened() const;
            void setFlashFrightened(bool frightened);

    };
}