#pragma once

#include "DirectionalAnimation.h"
#include "PacmanState.h"

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

            PacmanAnimationPack(const DirectionalAnimation& normal, const DirectionalAnimation& circle)
                                : normal_(normal), circle_(circle)
            {

            }
            
            

            DirectionalAnimation& animationFor(PacmanState state)
            {
                switch (state)
                {
                    case PacmanState::Normal:
                        return normal_;
                    case PacmanState::Circle:
                        return circle_;
                    default:
                        return normal_;
                }
            }

             void update(sf::Time dt)
            {
                normal_.update(dt);
            }
        private:
            DirectionalAnimation normal_;
            DirectionalAnimation circle_;

            // DirectionalAnimation dying_;
    };

}