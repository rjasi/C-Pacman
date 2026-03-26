#pragma once

#include "Maze.h"
#include "Dir.h"
#include "PacmanState.h"

#include <SFML/Graphics.hpp>

// TODO: This class needs all pacman specific logic moved out and into a new class Pacman (or pacman entity)
// that inherits from this class. 
// ghost entity class already do this

namespace Pacman
{
    /*
    Idea behind tile movement 
    
    start at current tile (centered).
    
    set target tile to 1 step in current direction from current tile
    
    move
    
    once movement crosses target tile'ss center on a tick, snap to the center of that tile
    at this point do checks such as wall

    on direction reversals swap current_tile and target tile

    same idea with early cornerning, just move diagonally for a bit and snap current
    direction's movement axis to junction center axis (i.e moving right, once movement will cross x center on junction tile snap) 
    then cornering is done
    */

    class MoveableEntity
    {
        public:
            MoveableEntity(const TileRC& startingTile, const sf::Vector2f& startingPos);
            MoveableEntity() = delete;
            static constexpr float CORNERING_EPS = 4.0f;
            void setPosition(const sf::Vector2f& p, const TileRC& tile);

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
            virtual ~MoveableEntity() = default;
            bool visible() const;
            void setVisible(bool visible);  

            // todo move these into own pacman entity class
            PacmanState state() const;
            void setState(PacmanState state);
            virtual void reset();
            static constexpr float BASE_SPEED = 75.75757625f;

        protected: 
            bool tryWarp(const Maze& maze);
            void move(sf::Time dt);
            void move(sf::Time dt, Dir d);
            sf::Vector2f pos_{};
            Dir current_ = Dir::Right;
            Dir requested_ = Dir::Right;
            float speed_ = 1.f; // % based on base speed
            bool visible_ = true;
            TileRC currentTile_;
            TileRC targetTile_;

            sf::Vector2f prevCenter_;
            sf::Vector2f targetCenter_;

            // bit of math magic. given 2 positions, did it cross a point (boundary)
            // used to determine if entity has crossed tile center
            bool crossed(float prev, float curr, float boundary) const;
            bool crossedCenter(const Maze& maze, const sf::Vector2f& prev) const;


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
            void tryStartEarlyCornering(sf::Time dt, const Maze& maze, const sf::Vector2f& prev);
            void reverseDirection();
            bool isPerpendicularTurn() const;
            bool inTurningWindow(const Maze& maze, const sf::Vector2f& prev) const;
            bool trySnapToTile(const Maze& maze, Dir d);
            bool corneringFinished(const Maze& maze, const sf::Vector2f& prev);
            void snapToJunction(const Maze& maze);

            PacmanState state_ = PacmanState::Normal;
            int pauseMovementCount = 0;


            // below functions are a quick but badly coupled way to reset the pacman died animation 
            // once per death. TODO it should be moved to some kind of messaging system where world 
            // class requests animations to be reset

            mutable bool resetDiedAnimation_ = false;

        // below are pacman specific functions, todo move them out
        public:

            void requestResetDiedAnimation()
            {
                resetDiedAnimation_ = true;
            }

            bool consumeDiedAnimRequest() const
            {
                if (resetDiedAnimation_)
                {
                    resetDiedAnimation_ = false;
                    return true;
                }

                return false;
            }

            void pelletEaten()
            {
                pauseMovementCount+=1;
            }

            void powerPelletEaten()
            {
                pauseMovementCount+=3;
            }

    };
};