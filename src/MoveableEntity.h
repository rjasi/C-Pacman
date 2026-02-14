#pragma once

#include "Maze.h"
#include "Dir.h"
#include <SFML/Graphics.hpp>

namespace Pacman
{

    class MoveableEntity
    {
        public:
            static constexpr float CORNERING_EPS = 4.0f;
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
            void move(sf::Time dt, Dir d);
            sf::Vector2f pos_{};
            Dir current_ = Dir::Right;
            Dir requested_ = Dir::Right;
            float speed_ = 60.f;

        private:
            // hold info about when cornering started
            class CorneringContext
            {
                public: 
                    Dir cornerDir = Dir::None;
                    bool corneringStarted = false;
                    TileRC junctionTile = {0,0}; // tile cornering is going through

                    void clear()
                    {
                        cornerDir = Dir::None;
                        corneringStarted = false;
                        junctionTile = {0,0};
                    }
            };

            CorneringContext corneringContext_;

            bool isTurning();
            bool notPastTurningPoint(const Maze& maze) const;
            void tryStartEarlyCornering(sf::Time dt, const Maze& maze);
            void reverseDirection();
            bool isPerpendicularTurn() const;
            bool inTurningWindow(const Maze& maze) const;
            bool trySnapToTile(const Maze& maze, Dir d);
            bool corneringFinished(const Maze& maze);
            void snapToJunction(const Maze& maze);

    };
};