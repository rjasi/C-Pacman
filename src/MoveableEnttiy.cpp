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

    bool MoveableEntity::isTurning()
    {
        return current_ != DirUtils::opposite(requested_) 
        && current_ != requested_ 
        && requested_ != Dir::None;
    }

    bool MoveableEntity::notPastTurningPoint(const Maze& maze) const
    {
        // don't start turns if past center of dir perpendicular current_
        // otherwise sprite will be moved up without turning causing 
        // a graphical bug
        sf::Vector2f center = maze.tileCenter(pos_);
        if ((current_ == Dir::Right && pos_.x > center.x)
            || (current_ == Dir::Left && pos_.x < center.x)
            || (current_ == Dir::Up && pos_.y < center.y)
            || (current_ == Dir::Down && pos_.y > center.y)
        
        )
        {
            return false;
        }
        return true;
    }

    bool MoveableEntity::isPerpendicularTurn() const
    {
        return 
        (DirUtils::isHorizontal(current_) && DirUtils::isVertical(requested_)) 
        || (DirUtils::isVertical(current_) && DirUtils::isHorizontal(requested_));
    }

    bool MoveableEntity::inTurningWindow(const Maze& maze) const
    {
        // pacman can start turning 3 pixels before the center of a junction 

        // currently going left or right, and next direction is up or down
        // check if x is close enough
        if (DirUtils::isHorizontal(current_) && DirUtils::isVertical(requested_))
        {
            return maze.nearTileCenterX(pos_, CORNERING_EPS);
        }
        // same going but if currently going up or down check if y is close enoughs
        else if (DirUtils::isVertical(current_) && DirUtils::isHorizontal(requested_))
        {
            return maze.nearTileCenterY(pos_, CORNERING_EPS);
        }

        return false;
    }


    void MoveableEntity::tryStartEarlyCornering(sf::Time dt, const Maze& maze)
    {
        // logic: once a perpendicular turn is requested 
        // if pacman is close enough to the center of a tile 
        // and the next tile in requested direction is not a wall (enterable) (also a junction in this case)
        // and not past turning point (allow slightly late input)
        // then start turning

        // below used to fix a visual bug
        // ex: current_ = Right, press up, start going diagonally up
        // and then immediately press right quickly. if quick enough pacman will have moved up a bit 
        // but still going Right and now probably clipping maze
        // prevent changing direction once commited
        if (corneringContext_.corneringStarted)
        {
            return;
        }

        const bool turnRequested = isTurning();
        const bool perpendicularTurn = isPerpendicularTurn();
        const bool isNotPastTurnPoint = notPastTurningPoint(maze);
        const bool isInTurningWindow = inTurningWindow(maze);
        const bool nextTileInReqestedDirectionEnterable = maze.canEnterNextTile(requested_, pos_);
        const bool canStartCornering = turnRequested && perpendicularTurn && isNotPastTurnPoint 
        && isInTurningWindow && nextTileInReqestedDirectionEnterable;
        
        if (!canStartCornering)
        {
            return;
        }

        corneringContext_.corneringStarted = true;
        corneringContext_.cornerDir = requested_;
        corneringContext_.junctionTile = maze.worldToTile(pos_);
    }

    bool MoveableEntity::trySnapToTile(const Maze& maze, Dir d)
    {
        // if travelling left to right, snap to x if close enough

        if (DirUtils::isHorizontal(d) && maze.nearTileCenterX(pos_, centerEps()))
        {
            pos_.x = maze.tileCenter(pos_).x;
            return true;
        }
        // same logic but for up/down
        else if (DirUtils::isVertical(d) && maze.nearTileCenterY(pos_, centerEps()))
        {
            pos_.y = maze.tileCenter(pos_).y;
            return true;
        }
        else if (maze.nearTileCenter(pos_, centerEps())) // when direction is None center on both axis
        {
            pos_ = maze.tileCenter(pos_);
            return true;
        }
        return false;
    }

    // cornering is finished when current_ dir movement axis snaps to junction tile
    // i.e current_ =  left or right , snap to x center of junction tile when close enough
    bool MoveableEntity::corneringFinished(const Maze& maze)
    {
        sf::Vector2f junctionCenter = maze.tileCenter(corneringContext_.junctionTile);

        if (DirUtils::isHorizontal(current_))
        {
            return std::abs(junctionCenter.x - pos_.x) <= centerEps();
        }
        else if (DirUtils::isVertical(current_))
        {
            return std::abs(junctionCenter.y - pos_.y) <= centerEps();
        }
        return false;
    }

    void MoveableEntity::snapToJunction(const Maze& maze)
    {
        // only call when corneringFinished let us know we are close enough to snap to junction 
        // seperate the logic to make things a bit more clear to understand
        sf::Vector2f junctionCenter = maze.tileCenter(corneringContext_.junctionTile);
        if (DirUtils::isHorizontal(current_))
        {
            pos_.x = junctionCenter.x;
        }
        else if (DirUtils::isVertical(current_))
        {
            pos_.y = junctionCenter.y;
        }
    }


    void MoveableEntity::update(sf::Time dt, const Maze& maze)
    {
        // diagonal movement, start early if at least 3 pixels aeay from center

        tryStartEarlyCornering(dt, maze);
        

        // reverse direction immediately or set new direction immidiately if stopped
        if ((current_ == Dir::None || current_ == DirUtils::opposite(requested_)) 
            && !corneringContext_.corneringStarted)
        {
            current_ = requested_;
        }


        if (corneringContext_.corneringStarted && corneringFinished(maze))
        {
            snapToJunction(maze);
            current_ = corneringContext_.cornerDir;
            corneringContext_.clear();
        }
        // only check next tile once center snapped to current tile
        else if (!corneringContext_.corneringStarted && trySnapToTile(maze, current_))
        {
            if (maze.canEnterNextTile(requested_, pos_))
            {
                current_ = requested_;
            }

            if (!maze.canEnterNextTile(current_, pos_))
            {
                current_ = Dir::None;
            }
        }

        move(dt, corneringContext_.cornerDir);
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

    void MoveableEntity::move(sf::Time dt, Dir d)
    {
        sf::Vector2f step = DirUtils::dirVecWorld(d) * (speed_ * dt.asSeconds());
        pos_ += step;
    }

}