#include "Ghost.h"
#include "PathQuery.h"
#include "Random.h"

#include <iostream>

namespace Pacman
{

    Ghost::Ghost(const IGhostTargetStrategy& ghostTargetStrategy, 
        const IPathingStrategy& pathingStrategy, GameCharacters name,
        const TileRC& houseTile,
        const TileRC& startingTile,
        const sf::Vector2f startingPos)
    : MoveableEntity(startingTile, startingPos), 
    ghostTargetStrategy_(&ghostTargetStrategy),
    pathingStrategy_(&pathingStrategy),
    name_(name),
    houseTile_(houseTile)
    {
        speed_ = 20.0f;
    }

    GameCharacters Ghost::name() const
    {
        return name_;
    }

    // only used by GhostDirector to reverse direction on phase change
    void Ghost::requestReverseDirection()
    {
        reverseRequested_ = true;
    }

    bool Ghost::flashFrightened() const
    {
        return flashFrightened_;
    }

    void Ghost::setFlashFrightened(bool frightened)
    {
        flashFrightened_ = frightened;
    }


    void Ghost::setState(GhostState state)
    {
        state_ = state;
    }

    void Ghost::setHouseState(HouseState state)
    {
        houseState_ = state;
    }

    bool Ghost::isOutsideHouse() const
    {
        return houseState_ == HouseState::Outside;
    }

    GhostState Ghost::state() const
    {
        return state_;
    }

    HouseState Ghost::houseState() const
    {
        return houseState_;
    }

    void Ghost::update(sf::Time dt, const Maze& maze)
    {
        // scripted house state
        if (!isOutsideHouse())
        {
            switch (houseState_)
            {
                case HouseState::InHouse:
                    paceInHouse(dt, maze);
                    break;
       
                case HouseState::LeavingGettingToHouseCenter:
                    // scripted logic here: 
                    // assume ghost is pacing up and down first
                    // need to first align vertically of house center
                    // then need to align horizontally of house center
                    // finally ghost is aligned and can leave

                    if(!moveToHouseVerticalCenter(dt, maze))
                        return; 

                    if(!moveToTileHorizontalCenter(dt, maze, Maze::HOUSE_CENTER))
                        return; 

                    houseState_ = HouseState::Exiting;
                    break;
                case HouseState::Exiting:
                    // will set the state to outside once done
                    // maybe change the api to keep it consistent
                    moveToInfrontOfDoor(dt, maze);
                    break;
                case HouseState::EnteringGettingToHouseCenter:
                    // scripted logic here: 
                    // when ghostEaten path finding is done. it will be on either 
                    // Maze::INFRONT_DOOR_LEFT or INFRONT_DOOR_RIGHT
                    // so center horizontally first to house center
                    // the verticaly to the house center

                    if(!moveToHouseHorizontalCenter(dt, maze))
                        return; 

                    if(!moveToHouseVerticalCenter(dt, maze))
                        return; 
                    
                    houseState_ = HouseState::GettingToCorner;
                    break;
                case HouseState::GettingToCorner:
                    if (!moveToTileHorizontalCenter(dt, maze, houseTile_))
                        return;
                    
                    state_ = GhostState::Chase;
                    // todo make ghost director determine when to release ghost
                    // for now just release immiediately
                    houseState_ = HouseState::LeavingGettingToHouseCenter;
                    justEnteredHouse_ = true;
                    return;
                default:
                    break;
            }
            
            return;
        }

        switch (state_)
        {
            case GhostState::Chase:
                active(dt, maze);
                break;
            case GhostState::Scatter:
                active(dt, maze);
                break;
            case GhostState::EatenReturning:
                eatenReturning(dt, maze);
                break;
            case GhostState::Frightened:
                frightened(dt, maze);
                break;

        }

        
    }

    void Ghost::paceInHouse(sf::Time dt, const Maze& maze)
    {
        speed_ = 20.f;
        // todo refactor when ghost changes state and send back into house
        if (current_ == Dir::Left || current_ == Dir::Right)
        {
            current_ = Dir::Up;
        }

        // sf::Vector2f step = DirUtils::dirVecWorld(current_) * (speed_ * dt.asSeconds());
        // sf::Vector2f nextPos = pos_ + step;

        // when pacing, go up or down till wall then reverse direction
        // note: maze.nearTileCenter(pos_)  won't work because ghosts are 
        // aligned at tile boundary on x axis when pacing in the house

        // todo maybe clamp to x boundary? 

        if (!maze.canEnterNextTile(current_, pos_))
        {
            // pos_ = maze.tileCenterClampX(maze.worldToTile(pos_));
            current_ = current_ == Dir::Down ? Dir::Up : Dir::Down;
        }

        move(dt);
    }

    bool Ghost::moveToHouseVerticalCenter(sf::Time dt, const Maze& maze)
    {
        speed_ = 60.f;
        sf::Vector2f target = maze.tileToWorldOnBoundary(Maze::HOUSE_CENTER);

        // first center y and clamp if close enougb
        if (std::abs(pos_.y - target.y) <= Maze::CENTER_EPS)
        {
            pos_.y = target.y;
            return true;
        } 
        else if (pos_.y < target.y)
        {
            current_ = Dir::Down;
            //move down
            move(dt);
        }
        else if (pos_.y > target.y)
        {
            current_ = Dir::Up;
            // move up
            move(dt);
        }

        return false;

    }


    bool Ghost::moveToHouseHorizontalCenter(sf::Time dt, const Maze& maze)
    {
        speed_ = 60.f;
        sf::Vector2f target = maze.tileToWorldOnBoundary(Maze::HOUSE_CENTER);

        if (std::abs(pos_.x - target.x) <= Maze::CENTER_EPS)
        {
            pos_.x = target.x;
            return true;
        } 
        else if (pos_.x < target.x)
        {
            current_ = Dir::Right;
            move(dt);
        }
        else if (pos_.x > target.x)
        {
            current_ = Dir::Left;
            move(dt);
        }

        return false;
    }

    bool Ghost::moveToTileHorizontalCenter(sf::Time dt, const Maze& maze, const TileRC& targetTile)
    {
        speed_ = 60.f;
        sf::Vector2f target = maze.tileToWorldOnBoundary(targetTile);

        if (std::abs(pos_.x - target.x) <= Maze::CENTER_EPS)
        {
            pos_.x = target.x;
            return true;
        } 
        else if (pos_.x < target.x)
        {
            current_ = Dir::Right;
            move(dt);
        }
        else if (pos_.x > target.x)
        {
            current_ = Dir::Left;
            move(dt);
        }

        return false;
    }

    // actually exit the house
    void Ghost::moveToInfrontOfDoor(sf::Time dt, const Maze& maze)
    {
        sf::Vector2f target = maze.tileToWorldOnBoundary(Maze::INFRONT_DOOR_LEFT);
        speed_ = 60.f;
        // guranteed to be alinged on x from moveToExit so no need to check y 
        // first center y and clamp if close enougb
        if (std::abs(pos_.y - target.y) <= Maze::CENTER_EPS)
        {
            pos_.y = target.y;
            current_ = Dir::Left; //todo randomly choose left or right
            // state_ = GhostState::Chase; let ghost director handle this
            // if going left then current tile is always INFRONT_OF_DOOR_RIGHT
            currentTile_ = Maze::INFRONT_DOOR_RIGHT;
            targetTile_ = PathUtils::step(current_, currentTile_);
            houseState_ = HouseState::Outside;
        } 
        else if (pos_.y < target.y)
        {
            current_ = Dir::Down;
            //move down
            move(dt);
        }
        else if (pos_.y > target.y)
        {
            current_ = Dir::Up;
            // move up
            move(dt);
        }
    }

    void Ghost::eatenReturning(sf::Time dt, const Maze& maze)
    {
        // only need path finding when outside house
        // once pathfinding is done it sets houseState_ = HouseState::EnteringGettingToHouseCenter;
        // from then on scripted movements will take over
        if (!isOutsideHouse())
        {
            return;
        }

        speed_ = 150.f;
        sf::Vector2f prev = pos_;
        move(dt);


        if (crossedCenter(maze, prev)) 
        {
            pos_ = maze.tileCenter(pos_);
            currentTile_ = targetTile_;
        }
        else
        {
            return;
        }

         if (tryWarp(maze))
        {
            return;
        }

        if (ghostTargetStrategy_ == nullptr || pathingStrategy_ == nullptr || targetContext_ == nullptr)
        {
            return;
        }

        if (currentTile_ == Maze::INFRONT_DOOR_LEFT || currentTile_ == Maze::INFRONT_DOOR_RIGHT)
        {
            houseState_ = HouseState::EnteringGettingToHouseCenter;
            return;
        }

        PathQuery query = 
        {
            .current_tile = maze.worldToTile(pos_),
            .current_direction = current_,
            .target_tile = Maze::INFRONT_DOOR_LEFT, // according to pacman dossier it always targets that tile
            .canReverse = false
        };

        current_ = pathingStrategy_->chooseNext(maze, query);
        targetTile_ = PathUtils::step(current_, currentTile_);

        targetContext_ =  nullptr; // reset
    }


    // randomly choose directions at tile center except reverse if possible
    void Ghost::frightened(sf::Time dt, const Maze& maze)
    {
        speed_ = 20.f;
        sf::Vector2f prev = pos_;
        move(dt);

        if (reverseRequested_) 
        {
            reverseRequested_ = false;
            current_ = DirUtils::opposite(current_);
            std::swap(currentTile_, targetTile_);
            targetContext_ =  nullptr; 
            return;
        }

        // only choose direction at tile center
        if (crossedCenter(maze, prev)) 
        {
            pos_ = maze.tileCenter(pos_);
            currentTile_ = targetTile_;
        }
        else
        {
            return;
        }

        if (tryWarp(maze))
        {
            return;
        }

        std::vector<Dir> validDirs;
        validDirs.reserve(4);

        TileRC current_tile = maze.worldToTile(pos_);

        for (Dir d : {Dir::Left, Dir::Right, Dir::Up, Dir::Down})
        {
            if (d == DirUtils::opposite(current_))
            {
                continue;
            }

            TileRC next = PathUtils::step(d, current_tile);

            if (!maze.isWall(next) || maze.isInWarpTunnel(next))
            {
                validDirs.push_back(d);
            }
        }

        if (validDirs.size() <= 0)
        {
            current_ = DirUtils::opposite(current_);
            return; 
        }
    
        current_ = validDirs[randomInt(0, validDirs.size() - 1)]; 
        targetTile_ = PathUtils::step(current_, current_tile);
    }


    // determine where to go
    void Ghost::active(sf::Time dt, const Maze& maze)
    {
        speed_ = 60.f;
        sf::Vector2f prev = pos_;
        move(dt);

        // go in reverse direction at least one tick
        // todo check if ghost possibly clips maze a bit
        // i.e center on tile at wall on left. reversed is left
        // clips wall for one tick? 
        if (reverseRequested_) 
        {
            reverseRequested_ = false;
            current_ = DirUtils::opposite(current_);
            std::swap(currentTile_, targetTile_);
            targetContext_ =  nullptr; 
            return;
        }

        // only choose direction at tile center
        if (crossedCenter(maze, prev)) 
        {
            pos_ = maze.tileCenter(targetTile_);
            currentTile_ = targetTile_;
        }
        else
        {
            return;
        }

        if (maze.shouldWarp(pos_))
        {
            // std::cerr << "warped\n";
            maze.applyWarp(pos_, currentTile_);
            targetTile_ = PathUtils::step(current_, currentTile_);
            return;
        }

        if (ghostTargetStrategy_ == nullptr || pathingStrategy_ == nullptr || targetContext_ == nullptr)
        {
            return;
        }

        TileRC target = state_ == GhostState::Chase ? ghostTargetStrategy_->getTarget(*targetContext_)
                                                    : ghostTargetStrategy_->scatterTarget(*targetContext_);

        PathQuery query = 
        {
            .current_tile = maze.worldToTile(pos_),
            .current_direction = current_,
            .target_tile = target,
            .canReverse = false
        };

        current_ = pathingStrategy_->chooseNext(maze, query);
        targetTile_ = PathUtils::step(current_, currentTile_);
        targetContext_ =  nullptr; // reset
    }

    void Ghost::setTargetContext(const TargetContext& ctx)
    {
        targetContext_ = &ctx;
    }

    float Ghost::centerEps() const
    {
        return 0.30f; // MAKE SURE THIS IS < dirVec(current_) * (speed_ * dt.asSeconds())
        // issue: 
        // pos at 1.0, move 0.24, get 1.24 
        // if eps is 0.25, it wil snap to center of current tile so you never move
        // setting too small will cause to almost never center if the speed is too high
    }
    



}