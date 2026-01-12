#pragma once

#include "Animation.h"
#include "Dir.h"
#include "TextureCache.h"

namespace Pacman
{
    class DirectionalAnimation
    {
        public: 
            const Animation* up   = nullptr;
            const Animation* down = nullptr;
            const Animation* left = nullptr;
            const Animation* right= nullptr;

            const Animation* clipFor(Dir d) const 
            {
                switch (d) 
                {
                    case Dir::Up:    return up;
                    case Dir::Down:  return down;
                    case Dir::Left:  return left;
                    case Dir::Right: return right;
                    default:         return nullptr; // throw exception
                }
            }
    };

    class AnimationLibrary
    {
        public: 
            AnimationLibrary(TextureCache& cache);

            DirectionalAnimation pacman;
            Animation pacmanRight_; // for now just use pacmanRight and rotate 

            DirectionalAnimation blinky;
            void loadAll(TextureCache& cache);
            void update(sf::Time dt);
            Animation blinkyRight_;

        private:

            
            // Animation pacmanUp_;
            // Animation pacmanLeft_;
            // Animation pacmanDown_;


            // sf::Sprite atlas_;
    };
}