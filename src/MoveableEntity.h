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
            sf::Vector2f pos_{};
            Dir current_ = Dir::Right;
            Dir requested_ = Dir::Right;
            float speed_ = 60.f;

            sf::Vector2f dirVec(Dir d) const;
            bool canEnter(Dir d, sf::Vector2f pos, const Maze& maze) const;
    };
};