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
                // const Ghost& g = static_cast<const Ghost&>(e); TODO pacman states

                // todo maybe move this logic out of Animation resolver 
                // keep lastDirection_ in PacmanEnttiy?
                if (e.direction() != Dir::None)
                {
                    lastDirection_ = e.direction();
                }

                Animation& clip = animPack_->animationFor(e.state()).clipFor(lastDirection_);
                
                if (e.direction() == Dir::None)
                {
                    clip.reset();
                }

                return clip;
            }

        private:
            Dir lastDirection_ = Dir::None;
            PacmanAnimationPack* animPack_;
    };
    
} // namespace Pacman
