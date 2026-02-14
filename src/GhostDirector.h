#pragma once

#include "Ghost.h"
#include "LevelConfig.h"


namespace Pacman
{
    class GhostDirector
    {
        private:
            int phaseIndex_ = 0;
            int pelletsEaten_ = 0;
            std::vector<GameCharacters> ghostsPendingRelease_ = {GameCharacters::Pinky, GameCharacters::Inky, GameCharacters::Clyde};
            LevelConfig cfg_;
            
            void tryReleaseGhost(const std::array<Ghost*, 4>& ghosts);


        public:
            GhostDirector() = delete;
            GhostDirector(const LevelConfig& cfg);
            
            void update(const std::array<Ghost*, 4>& ghosts, const Maze& maze, const TargetContext& ctx, sf::Time dt);
            void pelletEaten();

    };
}