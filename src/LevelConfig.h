#pragma once

#include "GhostState.h"


#include <SFML/Graphics.hpp>


namespace Pacman
{

    class Phase
    {
        public:
            GhostState mode;   // Scatter or Chase
            sf::Time  duration;
    };

    class LevelConfig
    {
        public: 
            // https://pacman.holenet.info/#CH2_Scatter_Chase_Repeat
            // ghosts swap between scatter and chase for a few phases
            std::vector<Phase> phases;                 // scatter/chase schedule
            sf::Time frightenedDuration = sf::Time{};  // power pellet duration

            
            int pelletsToReleasePinky = 0;
            int pelletsToReleaseInky  = 30;
            int pelletsToReleaseClyde = 60;

    };



}