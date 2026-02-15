#pragma once

#include "GhostAnimationPack.h"
#include "PacmanAnimationPack.h"
#include "Ghost.h"

#include <iostream>

namespace Pacman
{

    class IAnimationResolver 
    {
        public: 
            virtual ~IAnimationResolver() = default;

            // Return the animation to use *right now* for this entity.
            virtual Animation& resolve(const MoveableEntity& e) = 0;
    };

    class GhostAnimationResolver : public IAnimationResolver
    {
        public:
            GhostAnimationResolver(GhostAnimationPack* animPack)
            :  animPack_(animPack)
            {

            }

            Animation& resolve(const MoveableEntity& e) override 
            {
                const Ghost& g = static_cast<const Ghost&>(e);
                return animPack_->animationFor(g)
                                .clipFor(g.direction());
            }


        private:
            GhostAnimationPack* animPack_;
    };

    class PacmanAnimationResolver : public IAnimationResolver
    {
        public: 
            PacmanAnimationResolver(PacmanAnimationPack* animPack)
            : animPack_(animPack)
            {

            }

            Animation& resolve(const MoveableEntity& e) override 
            {
                return *animPack_->animationFor().up_;
            }

        private:
            PacmanAnimationPack* animPack_;
    };
    
} // namespace Pacman
