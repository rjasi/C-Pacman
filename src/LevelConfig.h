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
            std::vector<Phase> phases = 
            {
                {GhostState::Scatter, sf::seconds(7.0f)},
                {GhostState::Chase, sf::seconds(20.0f)},
                {GhostState::Scatter, sf::seconds(7.0f)},
                {GhostState::Chase, sf::seconds(20.0f)},
                {GhostState::Scatter, sf::seconds(5.0f)},
                {GhostState::Chase, sf::seconds(20.0f)},
                {GhostState::Scatter, sf::seconds(5.0f)}
            };                 // scatter/chase schedule

            sf::Time frightenedDuration = sf::seconds(6.0f);  // power pellet duration
            int frightenedFlashes = 5;

            int pelletsToReleasePinky = 0;
            int pelletsToReleaseInky  = 30;
            int pelletsToReleaseClyde = 60;

            float pacmanSpeed = .8f;
            float ghostSpeed = .75f;
            float ghostTunnelSpeed = .4f;
            float frightGhostSpeed = .5f;

            static float GetPacmanSpeed(int level)
            {
                if (level == 1)
                {
                    return .8f;
                }
                else if (level <= 4)
                {
                    return .9f;
                }
                else if (level <= 20)
                {
                    return 1.f;
                }
                // level 21+ .9 speed
                return .9f;
            }

            static float GetGhostSpeed(int level)
            {
                if (level == 1)
                {
                    return .75f;
                }
                else if (level <= 4)
                {
                    return .85f;
                }
           
                // level 5+ .95 speed
                return .95f;
            }

            static float GetGhostFrightSpeed(int level)
            {
                if (level == 1)
                {
                    return .5f;
                }
                else if (level <= 4)
                {
                    return .55f;
                }

                return .6f;
            }

            static float GetGhostTunnelSpeed(int level)
            {
                if (level == 1)
                {
                    return .4f;
                }
                else if (level <= 4)
                {
                    return .45f;
                }
            
                return .5f;
            }

            static std::vector<Phase> GetPhases(int level)
            {
                if (level == 1)
                {
                    return std::vector<Phase>
                    {
                        {GhostState::Scatter, sf::seconds(7.0f)},
                        {GhostState::Chase, sf::seconds(20.0f)},
                        {GhostState::Scatter, sf::seconds(7.0f)},
                        {GhostState::Chase, sf::seconds(20.0f)},
                        {GhostState::Scatter, sf::seconds(5.0f)},
                        {GhostState::Chase, sf::seconds(20.0f)},
                        {GhostState::Scatter, sf::seconds(5.0f)}
                    };   
                }
                else if (level <= 4)
                {
                    return std::vector<Phase>
                    {
                        {GhostState::Scatter, sf::seconds(7.0f)},
                        {GhostState::Chase, sf::seconds(20.0f)},
                        {GhostState::Scatter, sf::seconds(7.0f)},
                        {GhostState::Chase, sf::seconds(20.0f)},
                        {GhostState::Scatter, sf::seconds(5.0f)},
                        {GhostState::Chase, sf::seconds(1033.0f)},
                        {GhostState::Scatter, sf::seconds(1.f/60.f)}
                    };  
                }
                
                return std::vector<Phase> 
                {
                    {GhostState::Scatter, sf::seconds(5.0f)},
                    {GhostState::Chase, sf::seconds(20.0f)},
                    {GhostState::Scatter, sf::seconds(5.0f)},
                    {GhostState::Chase, sf::seconds(20.0f)},
                    {GhostState::Scatter, sf::seconds(5.0f)},
                    {GhostState::Chase, sf::seconds(1037.0f)},
                    {GhostState::Scatter, sf::seconds(1.f/60.f)}
                };  
            }

            static sf::Time GetFrightenedTime(int level)
            {
                switch (level)
                {
                    case 1:
                        return sf::seconds(6.f);
                    case 2:
                        return sf::seconds(5.f);
                    case 3:
                        return sf::seconds(4.f);
                    case 4:
                        return sf::seconds(3.f);
                    case 5:
                        return sf::seconds(2.f);
                    case 6:
                        return sf::seconds(5.f);
                    case 7:
                    case 8:
                        return sf::seconds(2.f);
                    case 9:
                        return sf::seconds(1.f);
                    case 10:
                        return sf::seconds(5.f);
                    case 11:
                        return sf::seconds(2.f);
                    case 12:
                    case 13:
                        return sf::seconds(1.f);
                    case 14:
                        return sf::seconds(3.f);
                    case 15:
                    case 16:
                        return sf::seconds(1.f);
                    case 17:
                        return sf::seconds(0.f);
                    case 18:
                        return sf::seconds(1.f);
                }

                //19+ no more fright
                return sf::seconds(0.f);
            }

            static int GetFrightenedFlashCount(int level)
            {
                switch (level)
                {
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                        return 5;
                    case 9:
                        return 3;
                    case 10:
                    case 11:
                        return 5;
                    case 12:
                    case 13:
                        return 3;
                    case 14:
                        return 5;
                    case 15:
                    case 16:
                        return 3;
                    case 17:
                        return 0;
                    case 18:
                        return 3;
                }

                //19+ no more fright
                return 0;
            }

            static int GetClydePelletReleaseCount(int level)
            {
                switch (level)
                {
                    case 1:
                        return 90;
                    case 2:
                        return 50;
                    default:
                        return 0;
                }
            }

            static int GetInkyPelletReleaseCount(int level)
                {
                    switch (level)
                    {
                        case 1:
                            return 30;
                        default:
                            return 0;
                    }
                }

            static LevelConfig GetLevelConfig(int level)
            {
                return LevelConfig
                {
                    .pelletsToReleaseClyde = GetClydePelletReleaseCount(level),
                    .pelletsToReleaseInky = GetInkyPelletReleaseCount(level),
                    .frightenedDuration = GetFrightenedTime(level),
                    .frightenedFlashes = GetFrightenedFlashCount(level),
                    .phases = GetPhases(level),
                    .pacmanSpeed = GetPacmanSpeed(level),
                    .ghostSpeed = GetGhostSpeed(level),
                    .ghostTunnelSpeed = GetGhostTunnelSpeed(level),
                    .frightGhostSpeed = GetGhostFrightSpeed(level),
                };
            }
    };



}