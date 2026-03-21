#include "MoveableEntity.h"
#include <iostream>
namespace Pacman
{

    MoveableEntity::MoveableEntity(const TileRC& startingTile, const sf::Vector2f& startingPos)
    : currentTile_(startingTile),
    pos_(startingPos),
    targetTile_(PathUtils::step(current_, currentTile_))
    {

    }

    void MoveableEntity::setPosition(const sf::Vector2f& p, const TileRC& tile)
    {
        currentTile_ = tile;
        pos_ = p;
        targetTile_ = PathUtils::step(current_, currentTile_);
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
        targetTile_ = PathUtils::step(current_, currentTile_);
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

    bool MoveableEntity::inTurningWindow(const Maze& maze, const sf::Vector2f& prev) const
    {
        // pacman can start turning 3 pixels before the center of a junction 

        // currently going left or right, and next direction is up or down
        // check if x is close enough
        sf::Vector2f tileCenter = maze.tileCenter(targetTile_); // use current pos. 
        if (DirUtils::isHorizontal(current_) && DirUtils::isVertical(requested_))
        {
            return crossed(prev.x, pos_.x, tileCenter.x - CORNERING_EPS)
            || crossed(prev.x, pos_.x, tileCenter.x + CORNERING_EPS);
            // return maze.nearTileCenterX(pos_, CORNERING_EPS);
        }
        // same going but if currently going up or down check if y is close enoughs
        else if (DirUtils::isVertical(current_) && DirUtils::isHorizontal(requested_))
        {
            return crossed(prev.y, pos_.y, tileCenter.y - CORNERING_EPS)
            || crossed(prev.y, pos_.y, tileCenter.y + CORNERING_EPS);
            // return maze.nearTileCenterY(pos_, CORNERING_EPS);
        }

        return false;
    }


    void MoveableEntity::tryStartEarlyCornering(sf::Time dt, const Maze& maze, const sf::Vector2f& prev)
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
        const bool isInTurningWindow = inTurningWindow(maze, prev);
        const bool nextTileInReqestedDirectionEnterable = maze.canEnterNextTile(requested_, targetTile_);
        const bool canStartCornering = turnRequested && perpendicularTurn && isNotPastTurnPoint 
        && isInTurningWindow && nextTileInReqestedDirectionEnterable;
        
        if (!canStartCornering)
        {
            return;
        }

        corneringContext_.corneringStarted = true;
        corneringContext_.cornerDir = requested_;
        corneringContext_.junctionTile = targetTile_;
    }

    bool MoveableEntity::crossedCenter(const Maze& maze, const sf::Vector2f& prev) const
    {
        // check if will cross next tile's center
        // TileRC nextTile = PathUtils::step(current_, currentTile_);
        sf::Vector2f tileCenter = maze.tileCenter(targetTile_);

        // std::cerr << "crossed " << crossed(prev.x, pos_.x, tileCenter.x) << "\n";
        if (DirUtils::isHorizontal(current_) && crossed(prev.x, pos_.x, tileCenter.x))
        {
            return true;
        }
        // same logic but for up/down
        else if (DirUtils::isVertical(current_) && crossed(prev.y, pos_.y, tileCenter.y))
        {
            return true;
        }

        return false;
    }

    // cornering is finished when current_ dir movement axis snaps to junction tile
    // i.e current_ =  left or right , snap to x center of junction tile when close enough
    bool MoveableEntity::corneringFinished(const Maze& maze, const sf::Vector2f& prev)
    {
        sf::Vector2f junctionCenter = maze.tileCenter(corneringContext_.junctionTile);

        if (DirUtils::isHorizontal(current_))
        {
            return crossed(prev.x, pos_.x, junctionCenter.x);
        }
        else if (DirUtils::isVertical(current_))
        {
            return crossed(prev.y, pos_.y, junctionCenter.y);
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
        currentTile_ = corneringContext_.junctionTile;
        targetTile_ = PathUtils::step(corneringContext_.cornerDir, currentTile_);
    }


    void MoveableEntity::update(sf::Time dt, const Maze& maze)
    {
        sf::Vector2f prev = pos_;
    
        move(dt, corneringContext_.cornerDir);
        move(dt);

        // diagonal movement, start early if at least 3 pixels aeay from center
        tryStartEarlyCornering(dt, maze, prev);

        // reverse direction immediately or set new direction immidiately if stopped
        if ((current_ == Dir::None || current_ == DirUtils::opposite(requested_)) 
            && !corneringContext_.corneringStarted)
        {
            if (maze.canEnterNextTile(requested_, currentTile_) 
            || maze.isInWarpTunnel(currentTile_) && DirUtils::isHorizontal(requested_) ) // allow switching from left to right in warp tunnel
            {
                // on reversals swap current and target
                if (current_ == DirUtils::opposite(requested_))
                {
                    std::swap(targetTile_, currentTile_);
                }
    
                current_ = requested_;
                requested_ = Dir::None;
            }
        }


        if (corneringContext_.corneringStarted && corneringFinished(maze, prev))
        {
            snapToJunction(maze);
            current_ = corneringContext_.cornerDir;
            corneringContext_.clear();
        }
        // only check next tile once center snapped to current tile
        else if (!corneringContext_.corneringStarted && crossedCenter(maze, prev))
        {
            currentTile_ = targetTile_;

            sf::Vector2f tileCenter = maze.tileCenter(targetTile_);
            //center 
            if (DirUtils::isHorizontal(current_))
            {
                pos_.x = tileCenter.x;
            } 
            else if (DirUtils::isVertical(current_))
            {
                pos_.y = tileCenter.y;
            }
            else
            {
                pos_ = tileCenter;
            }

            if (tryWarp(maze))
            {
                return;
            }

            if (maze.canEnterNextTile(requested_, pos_))
            {
                current_ = requested_;
                requested_ = Dir::None;
            }

            // allow going out of bounds when in WarpTunnel
            if (!maze.canEnterNextTile(current_, pos_) && !maze.isInWarpTunnel(currentTile_))
            {
                current_ = Dir::None;
            }

            targetTile_ = PathUtils::step(current_, currentTile_);
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
        sf::Vector2f step = DirUtils::dirVecWorld(current_) * (speed_ * BASE_SPEED * dt.asSeconds());
        pos_ += step;
    }

    void MoveableEntity::move(sf::Time dt, Dir d)
    {
        sf::Vector2f step = DirUtils::dirVecWorld(d) * (speed_ * BASE_SPEED * dt.asSeconds());
        pos_ += step;
    }

    bool MoveableEntity::visible() const
    {
        return visible_;
    }

    void MoveableEntity::setVisible(bool visible)
    {
        visible_ = visible;
    }

    bool MoveableEntity::crossed(float prev, float curr, float boundary) const
    {
        // std::cerr << prev << " " << curr << " " << boundary  << " " << (prev - boundary) * (curr - boundary) << " crosseds\n";
        return (prev - boundary) * (curr - boundary) <= 0.f;
    }

    bool MoveableEntity::tryWarp(const Maze& maze)
    {
        /*
            Warping logic:
            maze.canEnterNextTile does not allow turns out of bounds
                - keeps entity glued to warp tunnel
            allow going out of bounds when isInWarpTunnel = true
            teleport to otherside when past some predefined bounds
            let maze class handle warping location specifics
        */

        if (maze.applyWarp(pos_, currentTile_))
        {
            targetTile_ = PathUtils::step(current_, currentTile_);
            return true;
        }
        return false;
    }


    PacmanState MoveableEntity::state() const
    {
        return state_;
    }
    void MoveableEntity::setState(PacmanState state)
    {
        state_ = state;
    }

    void MoveableEntity::reset()
    {
        corneringContext_.clear();
        requested_ = Dir::None;
    }

}