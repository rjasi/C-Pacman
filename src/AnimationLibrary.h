#pragma once

#include "Animation.h"
#include "Dir.h"
#include "TextureCache.h"

namespace Pacman
{
    class DirectionalAnimation
    {
        public: 
            const Animation* up = nullptr;
            const Animation* down = nullptr;
            const Animation* left = nullptr;
            const Animation* right = nullptr;

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
            DirectionalAnimation pinky;
            DirectionalAnimation inky;
            DirectionalAnimation clyde;
            
            void update(sf::Time dt);
            Animation blinkyRight_;

            static constexpr sf::Time ghostFrameTime = sf::milliseconds(80);

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

            // sf::Sprite atlas_;
    };
}