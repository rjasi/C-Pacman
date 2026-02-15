#pragma once

#include "Animation.h"
#include "Dir.h"
#include "TextureCache.h"
#include "IAnimationResolver.h"
#include "GhostEnum.h"
#include "GhostAnimationPack.h"
#include "DirectionalAnimation.h"
#include "PacmanAnimationPack.h"

namespace Pacman
{
    class AnimationLibrary
    {
        public: 
            AnimationLibrary(TextureCache& cache);
            Animation pacmanRight_; // for now just use pacmanRight and rotate 

            DirectionalAnimation pacman_normal;

            DirectionalAnimation blinky_normal;
            DirectionalAnimation pinky_normal;
            DirectionalAnimation inky_normal;
            DirectionalAnimation clyde_normal;

            DirectionalAnimation blinky_fightened_ghost_directional_anim;
            DirectionalAnimation blinky_fightened_ghost_flash_directional_anim;
            DirectionalAnimation pinky_fightened_ghost_directional_anim;
            DirectionalAnimation pinky_fightened_ghost_flash_directional_anim;
            DirectionalAnimation inky_fightened_ghost_directional_anim;
            DirectionalAnimation inky_fightened_ghost_flash_directional_anim;
            DirectionalAnimation clyde_fightened_ghost_directional_anim;
            DirectionalAnimation clyde_fightened_ghost_flash_directional_anim;

            GhostAnimationPack blinky;
            GhostAnimationPack pinky;
            GhostAnimationPack inky;
            GhostAnimationPack clyde;

            PacmanAnimationPack pacman;

            void update(sf::Time dt);
            Animation blinkyRight_;

            static constexpr sf::Time ghostFrameTime = sf::milliseconds(80);
            static constexpr sf::Time ghostFrightenedFrameTime = sf::seconds(0.25f);

            std::array<std::unique_ptr<IAnimationResolver>, 4> ghostResolvers_;
            std::unique_ptr<IAnimationResolver> pacmanResolver_;

        private:

            
            // Animation pacmanUp_;
            // Animation pacmanLeft_;
            // Animation pacmanDown_;


            Animation blinkyLeft_;
            Animation blinkyUp_;
            Animation blinkyDown_;

            Animation pinkyRight_;
            Animation pinkyLeft_;
            Animation pinkyUp_;
            Animation pinkyDown_;

            Animation inkyRight_;
            Animation inkyLeft_;
            Animation inkyUp_;
            Animation inkyDown_;

            Animation clydeRight_;
            Animation clydeLeft_;
            Animation clydeUp_;
            Animation clydeDown_;


            Animation blinky_frightened_ghost_;
            Animation blinky_frightened_ghostFlash_;
            Animation pinky_frightened_ghost_;
            Animation pinky_frightened_ghostFlash_;
            Animation inky_frightened_ghost_;
            Animation inky_frightened_ghostFlash_;
            Animation clyde_frightened_ghost_;
            Animation clyde_frightened_ghostFlash_;
    };
}