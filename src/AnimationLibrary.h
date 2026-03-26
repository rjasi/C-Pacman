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

        private:
            Animation blinkyLeft_;
            Animation blinkyUp_;
            Animation blinkyDown_;
            Animation blinkyRight_;

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

            DirArray<Animation> blinkyEyes_;
            DirArray<Animation> pinkyEyes_;
            DirArray<Animation> inkyEyes_;
            DirArray<Animation> clydeEyes_;

        public: 
            static constexpr sf::Vector2f SPRITE_ORIGIN = {8.f, 8.f};
            // todo maybe move these to a factory class
            static DirArray<Animation> MakeEyes(sf::Texture& atlas);
            static DirArray<Animation> MakeNormalCharacter(sf::Texture& atlas, 
                                                            GameCharacters id,
                                                            int frameCountRow,
                                                            sf::Time frameTime,
                                                            sf::Vector2f origin = SPRITE_ORIGIN);

            static Animation MakeFrightenedGhost(sf::Texture& atlas, 
                                                    int frameCount,
                                                    sf::Time frameTime = ghostFrightenedFrameTime,
                                                    sf::Vector2f origin = SPRITE_ORIGIN);
            
            static Animation MakeFrightenedGhostFlash(sf::Texture& atlas, 
                                                    int frameCount,
                                                    sf::Time frameTime = ghostFrightenedFrameTime,
                                                    sf::Vector2f origin = SPRITE_ORIGIN);

            static GhostAnimationPack MakeGhostAnimationPack(sf::Texture& atlas, GameCharacters id);
            static Animation PacmanDying(sf::Texture& atlas, sf::Time frameTime, sf::Vector2f origin = SPRITE_ORIGIN);
            static PacmanAnimationPack MakePacmanAnimationPack(sf::Texture& atlas);
            static Animation PacmanCircle(sf::Texture& atlas, sf::Vector2f origin = SPRITE_ORIGIN);
            static Animation PacmanLarge(sf::Texture& atlas, sf::Time frameTime);



            AnimationLibrary(TextureCache& cache);

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

            DirectionalAnimation blinkyEyesDirectionalAnim_;
            DirectionalAnimation pinkyEyesDirectionalAnim_;
            DirectionalAnimation inkyEyesDirectionalAnim_;
            DirectionalAnimation clydeEyesDirectionalAnim_;

            GhostAnimationPack blinky;
            GhostAnimationPack pinky;
            GhostAnimationPack inky;
            GhostAnimationPack clyde;

            PacmanAnimationPack pacman;

            void update(sf::Time dt);

            static constexpr sf::Time ghostFrameTime = sf::milliseconds(80.f);
            static constexpr sf::Time pacmanFrameTime = sf::milliseconds(60.f);
            static constexpr sf::Time pacmanDyingFrameTime = sf::milliseconds(120.f);
            static constexpr sf::Time ghostFrightenedFrameTime = sf::seconds(0.25f);

            std::array<std::unique_ptr<IAnimationResolver>, 4> ghostResolvers_;
            std::unique_ptr<IAnimationResolver> pacmanResolver_;
    };
}