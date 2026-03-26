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
        tryReleaseGhost(ghosts, dt);

        if (powerPelletEaten_)
        {
            startFrightenedMode(ghosts);
        }

        if (!frightened_)
        {
            updatePhase(ghosts, dt);
        }
        else 
        {
            frightenMode(ghosts, dt);
        }

        for (Ghost* ghost : ghosts)
        {
            ghost->setTargetContext(ctx);
            ghost->update(dt, maze);
        }

    }

    void GhostDirector::tryReleaseGhost(const std::array<Ghost*, 4>& ghosts, sf::Time dt)
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
        else if (ghostToRelease->isOutsideHouse()) // should not happen but fail safe
        {
            ghostsPendingRelease_.erase(ghostsPendingRelease_.begin());
            return;
        }

        bool canRelease = false; 

        switch (ghostId)
        {
            case GameCharacters::Pinky:
                canRelease = (pelletsEaten_ >= cfg_.pelletsToReleasePinky) && !pinkyPelletCountRelease_;
                break;
            case GameCharacters::Inky:
                canRelease = (pelletsEaten_ >= cfg_.pelletsToReleaseInky) && !inkyPelletCountRelease_;
                break;
            case GameCharacters::Clyde:
                canRelease = (pelletsEaten_ >= cfg_.pelletsToReleaseClyde) && !clydePelletCountRelease_;
                break;
            default:
                return;
        }

        if (canRelease && ghostToRelease->houseState() == HouseState::InHouse)
        {
            ghostToRelease->setHouseState(HouseState::LeavingGettingToHouseCenter);
            ghostsPendingRelease_.erase(ghostsPendingRelease_.begin());

            switch (ghostId)
            {
                case GameCharacters::Pinky:
                    pinkyPelletCountRelease_ = true;
                    break;
                case GameCharacters::Inky:
                    inkyPelletCountRelease_ = true;
                    break;
                case GameCharacters::Clyde:
                    clydePelletCountRelease_ = true;
                    break;
                default:
                    break;
            }
            return;
        }

        // once pellet count release is done, release by timer
        if ((pinkyPelletCountRelease_ && ghostId == GameCharacters::Pinky) 
        || (inkyPelletCountRelease_ && ghostId == GameCharacters::Inky) 
        || (clydePelletCountRelease_ && ghostId == GameCharacters::Clyde))
        {
            releaseTimer_ += dt;
            if (releaseTimer_ >= TIME_TO_RELEASE_GHOST)
            {
                ghostToRelease->setHouseState(HouseState::LeavingGettingToHouseCenter);
                ghostsPendingRelease_.erase(ghostsPendingRelease_.begin());

                releaseTimer_ -= TIME_TO_RELEASE_GHOST;
            }
        }
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
                ghost->setFlashFrightened(false);

                if (ghost->state() == GhostState::Frightened)
                {
                    ghost->setState(GhostState::Chase);
                }

                if (ghost->isOutsideHouse())
                {
                    ghost->requestReverseDirection();
                }
            }
        }

        
        sf::Time flashThreshHold = FRIGHTENED_FLASH_DURATION * 2.0f * (float) cfg_.frightenedFlashes;

        if (cfg_.frightenedDuration - frightenedElapsed_ <= flashThreshHold)
        {
            frightenedFlashElapsed_ += dt;
            //std::cerr << frightenedElapsed_ << "\n";
        }
        else
        {
            // reset when frightenedElapsed_ sets reset i.e ghost duration extended 
            frightenedFlashElapsed_ = sf::Time{};
        }

        if (frightenedFlashElapsed_ >= FRIGHTENED_FLASH_DURATION)
        {
            frightenedFlashElapsed_ -= FRIGHTENED_FLASH_DURATION;
            // std::cerr << "flip" << "\n";
            for (Ghost* ghost : ghosts)
            {
                ghost->setFlashFrightened(!ghost->flashFrightened());
            }
        }
    }

    bool GhostDirector::isActive(GhostState state) const
    {
        return state == GhostState::Chase || state == GhostState::Scatter;
    }

    void GhostDirector::updatePhase(const std::array<Ghost*, 4>& ghosts, sf::Time dt)
    {
        elapsed_ += dt;

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

    void GhostDirector::restartLevel()
    {
        frightened_ = false;
        releaseTimer_ = sf::Time::Zero;
        ghostsPendingRelease_ = {GameCharacters::Pinky, GameCharacters::Inky, GameCharacters::Clyde};
    }

    void GhostDirector::startFrightenedMode(const std::array<Ghost*, 4>& ghosts)
    {
        // when frightened time is 0 just reverse direction
        if (cfg_.frightenedDuration <= sf::Time::Zero)
        {
            powerPelletEaten_ = false;
            for (Ghost* ghost : ghosts)
            {
                if (ghost->isOutsideHouse() && isActive(ghost->state()))
                {
                    ghost->requestReverseDirection();
                }
            }

            return;
        }


        // startFrightenedMode is also called when frightened mode is extended
        // if this is not an extension, then reset ghosts eaten score
        if (!frightened_)
        {
            ghostEaten_ = 0;

            // only reverse direction on new frightended trigger. if extended then no need to reverse direction
            for (Ghost* ghost : ghosts)
            {
                if (ghost->isOutsideHouse() && isActive(ghost->state()))
                {
                    ghost->requestReverseDirection();
                }
            }
        }

        powerPelletEaten_ = false;
        frightened_ = true;
        frightenedElapsed_ = sf::Time{};
        frightenedFlashElapsed_ = sf::Time{};

        for (Ghost* ghost : ghosts)
        {
            if (isActive(ghost->state()))
            {
                ghost->setState(GhostState::Frightened);
            }
            ghost->setFlashFrightened(false);
        }
    }


    void GhostDirector::powerPelletEaten()
    {
        powerPelletEaten_ = true;
    }

    int GhostDirector::ghostEaten()
    {
        return ++ghostEaten_;
    }

    int GhostDirector::ghostEatenCount() const
    {
        return ghostEaten_;
    }

    bool GhostDirector::frightened() const
    {
        return frightened_;
    }

    void GhostDirector::setLevelConfig(const LevelConfig& cfg)
    {
        cfg_ = cfg;
    }

    void GhostDirector::reset()
    {
        pinkyPelletCountRelease_ = false;
        inkyPelletCountRelease_ = false;
        clydePelletCountRelease_ = false;
        frightened_ = false;
        powerPelletEaten_ = false;
        ghostEaten_ = 0;
        phaseIndex_ = 0;
        pelletsEaten_ = 0;
        ghostEaten_ = 0;
        ghostsPendingRelease_ = {GameCharacters::Pinky, GameCharacters::Inky, GameCharacters::Clyde};

    }

}