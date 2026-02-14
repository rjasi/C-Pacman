

#include "Ghost.h"

namespace Pacman
{
    class GhostDirector
    {
        private:
            int phaseIndex_ = 0;

        public:
            struct Config
            {
                struct Phase
                {
                    GhostMode mode;   // Scatter or Chase
                    sf::Time  duration;
                };

                // https://pacman.holenet.info/#CH2_Scatter_Chase_Repeat
                // ghosts swap between scatter and chase for a few phases
                std::vector<Phase> phases;                 // scatter/chase schedule
                sf::Time frightenedDuration = sf::Time{};  // power pellet duration

                
                int pelletsToReleasePinky = 0;
                int pelletsToReleaseInky  = 30;
                int pelletsToReleaseClyde = 60;

            };

            void update(std::array<Ghost*>, sf::Time dt);

    }
}