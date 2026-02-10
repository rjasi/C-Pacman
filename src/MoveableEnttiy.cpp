#include "MoveableEntity.h"
#include <iostream>
namespace Pacman
{
    void MoveableEntity::setPosition(sf::Vector2f p)
    {
        pos_ = p;
    }

    sf::Vector2f MoveableEntity::position() const 
    { 
        return pos_; 
    }

    void MoveableEntity::warp() 
    { 

        // warp from left to right
        if (pos_.x < -8.0f)
        {
            pos_.x = 224.0f + 8.0f; 
        }
        // right to left
        else if (pos_.x > 224.0f + 8.0f)
        {
            pos_.x = -8.0f;
        }
    }

    void MoveableEntity::setSpeed(float pxPerSec) 
    { 
        speed_ = pxPerSec; 
    }
        
    float MoveableEntity::speed() const 
    { 
        return speed_; 
    }

    Dir MoveableEntity::direction() const 
    { 
        return current_; 
    }
       
    void MoveableEntity::requestDirection(Dir d) 
    { 
        requested_ = d; 
    }

    void MoveableEntity::setDirection(Dir d) 
    { 
        current_ = d; 
    }

    void MoveableEntity::update(sf::Time dt, const Maze& maze)
    {
        // Snap/turn only at tile centers 
        if (maze.nearTileCenter(pos_, centerEps())) 
        {
            pos_ = maze.tileCenter(pos_);
            bool canEnterRequested = maze.canEnterNextTile(requested_, pos_);
            bool warping = isWarping(requested_, pos_, maze);
            
            // only change dir if next tile is enterable keep moving otherwise
            if (canEnterRequested)
            {
                current_ = requested_;
            }

            // only stop movement if current direction cannot go no more
            bool canEnterCurrent = maze.canEnterNextTile(current_, pos_);
            if(!canEnterCurrent)
            {
                current_ = Dir::None;
            }
        }

        move(dt);
        warp();
    }

    float MoveableEntity::centerEps() const
    {
        return 0.40f; // MAKE SURE THIS IS < dirVec(current_) * (speed_ * dt.asSeconds())
        // issue: 
        // pos at 1.0, move 0.24, get 1.24 
        // if eps is 0.25, it wil snap to center of current tile so you never move
        // setting too small will cause to almost never center if the speed is too high
    }

    float MoveableEntity::tileSize() const 
    { 
        return 8.f; 
    }
    
    bool MoveableEntity::isWarping(Dir d, sf::Vector2f pos, const Maze& maze) const
    {
        //todo move this logic to maze does not belong here
        // sf::Vector2i t = maze.worldToTile(pos);
        // sf::Vector2i step{ (int)dirVec(d).x, (int)dirVec(d).y };
        // sf::Vector2i next = t + step;

        return false;
        // return maze.isInWarpTile(next.y, next.x); // remember x = horizonal = column, y = vertical = row
    }

    

    sf::Angle MoveableEntity::rotation() const
    {
        switch (current_) 
        {
            case Dir::Right: return sf::degrees(0);
            case Dir::Left:  return sf::degrees(180);
            case Dir::Up:    return sf::degrees(-90);
            case Dir::Down:  return sf::degrees(90);
            default:         return sf::degrees(0);
        }
    }

    void MoveableEntity::move(sf::Time dt)
    {
        sf::Vector2f step = DirUtils::dirVecWorld(current_) * (speed_ * dt.asSeconds());
        pos_ += step;
    }
}