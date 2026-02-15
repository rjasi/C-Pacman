#pragma once

#include "Ghost.h"
#include "LevelConfig.h"

#include <SFML/Graphics.hpp>


namespace Pacman
{
    class GhostDirector
    {
        private:
            int phaseIndex_ = 0;
            int pelletsEaten_ = 0;
            sf::Time elapsed_ = sf::Time{};
            sf::Time frightenedElapsed_ = sf::Time{};
            bool frightened_ = false;

            std::vector<GameCharacters> ghostsPendingRelease_ = {GameCharacters::Pinky, GameCharacters::Inky, GameCharacters::Clyde};
            LevelConfig cfg_;
            Phase currentPhase_;
            
            void tryReleaseGhost(const std::array<Ghost*, 4>& ghosts);
            void updatePhase(const std::array<Ghost*, 4>& ghosts);
            void frightenMode(const std::array<Ghost*, 4>& ghosts, sf::Time dt);
            bool isActive(GhostState state) const;
            
        public:
            GhostDirector() = delete;
            GhostDirector(const LevelConfig& cfg);
            
            void update(const std::array<Ghost*, 4>& ghosts, const Maze& maze, const TargetContext& ctx, sf::Time dt);
            void pelletEaten();
            void powerPelletEaten();

            void startLevel();

    };
}