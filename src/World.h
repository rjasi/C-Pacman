#pragma once

#include "Ghost.h"
#include "Maze.h"
#include "MoveableEntity.h"
#include "GhostTargetStrategies.h"
#include "GreedyManhattanPathingStrategy.h"
#include "LevelConfig.h"
#include "GhostDirector.h"

#include <SFML/Graphics.hpp>


namespace Pacman
{
    class World
    {
        private:
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
    };
}