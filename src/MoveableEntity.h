#pragma once

#include "Maze.h"
#include "Dir.h"
#include <SFML/Graphics.hpp>

namespace Pacman
{
    class MoveableEntity
    {
        public:
            void setPosition(sf::Vector2f p);

            sf::Vector2f position() const;

            void setSpeed(float pxPerSec);
            float speed() const;

            Dir direction() const;
            void requestDirection(Dir d);
            void setDirection(Dir d);
            virtual void update(sf::Time dt, const Maze& maze);
            sf::Angle rotation() const;
            sf::Angle rotationRad() const;

            virtual float tileSize() const;
            virtual float centerEps() const;

        protected: 
            void warp();
            bool isWarping(Dir d, sf::Vector2f pos, const Maze& maze) const;
            void move(sf::Time dt);
            sf::Vector2f pos_{};
            Dir current_ = Dir::Right;
            Dir requested_ = Dir::Right;
            float speed_ = 60.f;

        private:
            bool isTurning();
            bool notPastTurningPoint(const Maze& maze);
    };
};