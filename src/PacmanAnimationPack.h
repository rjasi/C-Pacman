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

            PacmanAnimationPack(const DirectionalAnimation& normal, 
                                const DirectionalAnimation& circle,
                                const DirectionalAnimation& dying,
                                const DirectionalAnimation& large)
            : normal_(normal), 
            circle_(circle),
            dying_(dying),
            large_(large)
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
                    case PacmanState::Dying:
                        return dying_;
                    case PacmanState::Large:
                        return large_;
                    default:
                        return normal_;
                }
            }

             void update(sf::Time dt)
            {
                normal_.update(dt);
                dying_.update(dt);
                large_.update(dt);
            }
        private:
            DirectionalAnimation normal_;
            DirectionalAnimation circle_;
            DirectionalAnimation dying_;
            DirectionalAnimation large_;
    };

}