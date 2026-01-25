#pragma once

#include "DirectionalAnimation.h"

namespace Pacman
{

    class PacmanAnimationPack
    {
        public:
            PacmanAnimationPack(DirectionalAnimation* normal,
                                DirectionalAnimation* dying = nullptr)
                                : normal_(normal), dying_(dying)
            {

            }
            

            DirectionalAnimation& animationFor()
            {
                return *normal_;
            }
        private:
            DirectionalAnimation* normal_;
            DirectionalAnimation* dying_;
    };

}