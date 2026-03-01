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
            DirectionalAnimation normal_;
            DirectionalAnimation frightened_;
            DirectionalAnimation frightenedFlash_;
            DirectionalAnimation eyes_;

        public:
            GhostAnimationPack(GameCharacters characterId, 
                                DirectionalAnimation& normal,
                                DirectionalAnimation& frightened,
                                DirectionalAnimation& frightenedFlash,
                                DirectionalAnimation& eyes)
                                : normal_(normal),
                                frightened_(frightened),
                                frightenedFlash_(frightenedFlash),
                                eyes_(eyes)
            {

            }

            GhostAnimationPack(GameCharacters characterId, 
                                DirectionalAnimation* normal,
                                DirectionalAnimation* frightened,
                                DirectionalAnimation* frightenedFlash,
                                DirectionalAnimation* eyes)
                                : normal_(*normal),
                                frightened_(*frightened),
                                frightenedFlash_(*frightenedFlash),
                                eyes_(*eyes)
            {

            }


            void update(sf::Time dt)
            {
                normal_.update(dt);
                frightened_.update(dt);
                frightenedFlash_.update(dt);
            }

            DirectionalAnimation& animationFor(const Ghost& ghost)
            {
                GhostState state = ghost.state();
                switch (state)
                {
                    case GhostState::Chase:
                    case GhostState::Scatter:
                        return normal_;
                    case GhostState::EatenReturning:
                        return eyes_;
                    case GhostState::Frightened:
                        return ghost.flashFrightened() ? frightenedFlash_ : frightened_;
                }
            }


    };
}