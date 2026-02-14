#include "GhostDirector.h"

namespace Pacman
{


    GhostDirector::GhostDirector(const LevelConfig& cfg)
    : cfg_(cfg)
    {

    }

    void GhostDirector::update(const std::array<Ghost*, 4>& ghosts, const Maze& maze, const TargetContext& ctx, sf::Time dt)
    {
        tryReleaseGhost(ghosts);

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
        else if (ghostToRelease->state() != GhostState::InHouse) // should not happen ghost pinky, inky and clyde always start InHouse
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

        if (canRelease && ghostToRelease->state() == GhostState::InHouse)
        {
            ghostToRelease->setState(GhostState::GettingToHouseCenter);
            ghostsPendingRelease_.erase(ghostsPendingRelease_.begin());
            return;
        }

        // todo time based release later

    }

    void GhostDirector::pelletEaten()
    {
        pelletsEaten_++;
    }

}