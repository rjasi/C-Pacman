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
            pos_ = maze.tileCenter(maze.worldToTile(pos_));

            if (requested_ != Dir::None && canEnter(requested_, pos_, maze))
                current_ = requested_;

            if (!canEnter(current_, pos_, maze))
                current_ = Dir::None;
        }

        if (current_ != Dir::None) 
        {
            sf::Vector2f step = dirVec(current_) * (speed_ * dt.asSeconds());
            pos_ += step;
        }
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

    sf::Vector2f MoveableEntity::dirVec(Dir d) const 
    {
        switch (d) 
        {
            case Dir::Right: return { 1.f,  0.f};
            case Dir::Left:  return {-1.f,  0.f};
            case Dir::Up:    return { 0.f, -1.f};
            case Dir::Down:  return { 0.f,  1.f};
            default:         return { 0.f,  0.f};
        }
    }

    
    bool MoveableEntity::canEnter(Dir d, sf::Vector2f pos, const Maze& maze) const
    {
        if (d == Dir::None) return false;

        sf::Vector2i t = maze.worldToTile(pos);
        sf::Vector2i step{ (int)dirVec(d).x, (int)dirVec(d).y };
        sf::Vector2i next = t + step;

        return !maze.isWall(next.y, next.x); // remember x = horizonal = column, y = vertical = row
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
}