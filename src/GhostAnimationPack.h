#pragma once

#include "GhostEnum.h"
#include "DirectionalAnimation.h"
#include "GhostState.h"
#include "Ghost.h"

namespace Pacman
{
    // for ghosts
    class GhostAnimationPack
    {
        private: 
            GameCharacters characterId;
            DirectionalAnimation* normal_;
            DirectionalAnimation* frightened_;
            DirectionalAnimation* frightenedFlash_;
            DirectionalAnimation* eyes_;

        public:
            GhostAnimationPack(GameCharacters characterId, 
                                DirectionalAnimation* normal,
                                DirectionalAnimation* frightened = nullptr,
                                DirectionalAnimation* frightenedFlash = nullptr,
                                DirectionalAnimation* eyes =  nullptr)
                                : normal_(normal),
                                frightened_(frightened),
                                frightenedFlash_(frightenedFlash),
                                eyes_(eyes)
            {

            }

            void update(sf::Time dt)
            {
                if (normal_ != nullptr) normal_->update(dt);
                if (frightened_ != nullptr) frightened_->update(dt);
                if (frightenedFlash_ != nullptr) frightenedFlash_->update(dt);
            }

            DirectionalAnimation& animationFor(const Ghost& ghost) const
            {
                GhostState state = ghost.state();
                switch (state)
                {
                    case GhostState::Chase:
                    case GhostState::Scatter:
                        return *normal_;
                    case GhostState::EatenReturning:
                        return *normal_;
                    case GhostState::Frightened:
                        return ghost.flashFrightened() ? *frightenedFlash_ : *frightened_;
                }
            }


    };
}