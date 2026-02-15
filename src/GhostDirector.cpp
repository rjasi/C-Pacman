#include "GhostDirector.h"
#include <iostream>

namespace Pacman
{


    GhostDirector::GhostDirector(const LevelConfig& cfg)
    : cfg_(cfg)
    {

    }

    void GhostDirector::update(const std::array<Ghost*, 4>& ghosts, const Maze& maze, const TargetContext& ctx, sf::Time dt)
    {
        elapsed_ += dt;
        tryReleaseGhost(ghosts);
        updatePhase(ghosts);

        for (Ghost* ghost : ghosts)
        {
            ghost->setTargetContext(ctx);
            ghost->update(dt, maze);
        }

    }

    void GhostDirector::tryReleaseGhost(const std::array<Ghost*, 4>& ghosts)
    {
        if (ghostsPendingRelease_.empty())
        {
            return;
        }

        GameCharacters ghostId = ghostsPendingRelease_.front();

        Ghost* ghostToRelease = nullptr;

        for (Ghost* ghost : ghosts)
        {
            if (ghost->name() == ghostId)
            {
                ghostToRelease = ghost; 
            }
        }

        if (ghostToRelease == nullptr)
        {
            return;
        }
        else if (ghostToRelease->isOutsideHouse()) // should not happen ghosts pinky, inky and clyde always start InHouse
        {
            ghostsPendingRelease_.erase(ghostsPendingRelease_.begin());
            return;
        }

        bool canRelease = false; 

        switch (ghostId)
        {
            case GameCharacters::Pinky:
                canRelease = pelletsEaten_ >= cfg_.pelletsToReleasePinky;
                break;
            case GameCharacters::Inky:
                canRelease = pelletsEaten_ >= cfg_.pelletsToReleaseInky;
                break;
            case GameCharacters::Clyde:
                canRelease = pelletsEaten_ >= cfg_.pelletsToReleaseClyde;
                break;
            default: // should never happen
                return;
        }

        if (canRelease && ghostToRelease->houseState() == HouseState::InHouse)
        {
            ghostToRelease->setHouseState(HouseState::GettingToHouseCenter);
            ghostsPendingRelease_.erase(ghostsPendingRelease_.begin());
            return;
        }

        // todo time based release later

    }

    void GhostDirector::pelletEaten()
    {
        pelletsEaten_++;
    }

    void GhostDirector::frightenMode(const std::array<Ghost*, 4>& ghosts, sf::Time dt)
    {
        if (frightened_ != true)
        {
            return;
        }

        frightenedElapsed_ += dt;

        if (frightenedElapsed_ > cfg_.frightenedDuration)
        {
            frightened_ = false;
            for (Ghost* ghost : ghosts)
            {
                if (ghost->state() == GhostState::Frightened)
                {
                    ghost->requestReverseDirection();
                    ghost->setState(GhostState::Chase);
                }
            }
            return; 
        }

        for (Ghost* ghost : ghosts)
        {
            if (ghost->state() == GhostState::Frightened)
            {
                ghost->requestReverseDirection();
                ghost->setState(GhostState::Chase);
            }
        }

        

    }

    bool GhostDirector::isActive(GhostState state) const
    {
        return state == GhostState::Chase || state == GhostState::Scatter;
    }


    void GhostDirector::updatePhase(const std::array<Ghost*, 4>& ghosts)
    {
        // chase indefinitely once phases are done
        if (cfg_.phases.size() <= 0)
        {
            for (Ghost* ghost : ghosts)
            {
                if (ghost->isOutsideHouse() && isActive(ghost->state()))
                {
                    ghost->setState(GhostState::Chase);
                }
            }
            return;
        }

        // when elapsed_ >= cfg_.phases.front().duration means it time for a phase change
        while (cfg_.phases.size() > 0 && elapsed_ >= cfg_.phases.front().duration)
        {

            // std::cerr << "GHOST PHASE :" << static_cast<int>(ghosts[0]->state()) << "\n";
            
            // spill remainder over to next phase
            elapsed_ -= cfg_.phases.front().duration;

            // remove done phase
            cfg_.phases.erase(cfg_.phases.begin());

            // if no more phases just put to chase mode
            if (cfg_.phases.size() <= 0)
            {
                for (Ghost* ghost : ghosts)
                {
                    if (ghost->isOutsideHouse() && isActive(ghost->state()))
                    {
                        ghost->setState(GhostState::Chase);
                    }
                }
                return; 
            }

            // reverse direction
            for (Ghost* ghost : ghosts)
            {
                if (ghost->isOutsideHouse() && isActive(ghost->state()))
                {
                    ghost->requestReverseDirection();
                }
            }
        }

        Phase currentPhase =  cfg_.phases.front();
        for (Ghost* ghost : ghosts)
        {
            if (ghost->isOutsideHouse() && isActive(ghost->state()))
            {
                ghost->setState(currentPhase.mode);
            }
        }
    }

    void GhostDirector::startLevel()
    {
        // currentPhase_ = cfg_.phases.front();
    }

    void GhostDirector::powerPelletEaten()
    {
        frightened_ = true;
        frightenedElapsed_ = sf::Time{};
    }



}