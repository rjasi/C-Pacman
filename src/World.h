#pragma once

#include "Ghost.h"
#include "Maze.h"
#include "MoveableEntity.h"
#include "GhostTargetStrategies.h"
#include "GreedyManhattanPathingStrategy.h"
#include "LevelConfig.h"
#include "GhostDirector.h"
#include "TextColors.h"
#include "Popup.h"

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>


namespace Pacman
{
    enum class WorldState
    {
        Playing = 0,
        GhostEaten,
        Died,
        LevelCleared
    };

    // class GhostEatenContext
    // {
    //     public:
    //         sf::Vector2f pos;
    // };

    class World
    {
        private:
            Ghost* eatenGhost = nullptr;
            WorldState state_ = WorldState::Playing;
            Maze maze_;
            MoveableEntity pacmanEntity_;
            Ghost blinky_;
            Ghost pinky_;
            Ghost inky_;
            Ghost clyde_;
            BlinkyTargetStrategy blinkyTargetStrategy_;
            PinkyTargetStrategy pinkyTargetStrategy_;
            InkyTargetStrategy inkyTargetStrategy_;
            ClydeTargetStrategy clydeTargetStrategy_;
            LevelConfig cfg_;
            GhostDirector ghostDirector_;
            
            std::vector<Popup> popups_;

            // pause for 1 sec 
            static constexpr sf::Time EATEN_PAUSE = sf::seconds(2.0f);
            sf::Time eatenTimer_{};


            GreedyManhattanPathingStrategy greedyManhattanPathingStrategy_;

            static constexpr TileRC BLINKY_SCATTER_CORNER = {-3, 27};
            static constexpr TileRC PINKY_SCATTER_CORNER = {-3, 0};
            static constexpr TileRC INKY_SCATTER_CORNER = {31, 27};
            static constexpr TileRC CLYDE_SCATTER_CORNER = {31, 0};
            // PinkyTargetStrategy inkyTargetStrategy_;
            // InkyTargetStrategy pinkyTargetStrategy_;
            // ClydeTargetStrategy clydeTargetStrategy_;

            sf::Time blinkElapsed_ = sf::Time::Zero;
            sf::Time blinkPeriod_  = sf::milliseconds(250); 
            bool powerPelletVisible_ = true;
            int score_ = 0;

            void resolveCollision();
            void playing(sf::Time dt);
            void ghostEaten(sf::Time dt);
            void advanceBlinkTimer(sf::Time dt);
            void updatePopups(sf::Time dt);

        public:
            World();

            const Maze& maze() const;
            const MoveableEntity& pacman() const;
            const MoveableEntity& blinky() const;
            const MoveableEntity& pinky() const;
            const MoveableEntity& inky() const;
            const MoveableEntity& clyde() const;

            bool powerPelletVisible() const;
            void setPlayerRequestedDir(Dir d);
            void update(sf::Time dt); 
            WorldState state() const;
            const std::vector<Popup>& popups() const;
    };
}