#pragma once

#include "DirectionalAnimation.h"

namespace Pacman
{

    class PacmanAnimationPack
    {
        public:
            // PacmanAnimationPack(DirectionalAnimation* normal,
            //                     DirectionalAnimation* dying = nullptr)
            //                     : normal_(normal), dying_(dying)
            // {

            // }

            PacmanAnimationPack(const DirectionalAnimation& normal)
                                : normal_(normal)
            {

            }
            
            

            DirectionalAnimation& animationFor()
            {
                return normal_;
            }

             void update(sf::Time dt)
            {
                normal_.update(dt);
            }
        private:
            DirectionalAnimation normal_;
            // DirectionalAnimation dying_;
    };

}