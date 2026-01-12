#pragma once

#include "Ghost.h"
#include "Maze.h"
#include "MoveableEntity.h"

#include <SFML/Graphics.hpp>


namespace Pacman
{
    class World
    {
        private:
            Maze maze_;
            MoveableEntity pacmanEntity_;
            Ghost blinky_;
            sf::Time blinkElapsed_ = sf::Time::Zero;
            sf::Time blinkPeriod_  = sf::milliseconds(250); 
            bool powerPelletVisible_ = true;
            int score_ = 0;

        public:
            World();

            const Maze& maze() const;
            const MoveableEntity& pacman() const;
            const MoveableEntity& blinky() const;

            bool powerPelletVisible() const;
            void setPlayerRequestedDir(Dir d);
            void update(sf::Time dt); 
    };
}