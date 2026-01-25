#pragma once

#include "GhostEnum.h"
#include "DirectionalAnimation.h"
#include "GhostState.h"

namespace Pacman
{
    // for ghosts
    class GhostAnimationPack
    {
        private: 
            GameCharacters characterId;
            DirectionalAnimation* normal_;
            DirectionalAnimation* frightened_;
            DirectionalAnimation* eyes_;

        public:
            GhostAnimationPack(GameCharacters characterId, 
                                DirectionalAnimation* normal,
                                DirectionalAnimation* frightened = nullptr,
                                DirectionalAnimation* eyes =  nullptr)
                                : normal_(normal),
                                frightened_(frightened),
                                eyes_(eyes)
            {

            }

            void update(sf::Time dt)
            {
                normal_->update(dt);
            }

            DirectionalAnimation& animationFor(GhostState state)
            {
                switch (state)
                {
                    case GhostState::Active:
                    case GhostState::GettingToHouseCenter:
                    case GhostState::InHouse:
                    case GhostState::LeavingHouse:
                        return *normal_;
                    case GhostState::EatenReturning:
                        return *normal_;
                    case GhostState::Frightened:
                        return *normal_;
                }
            }


    };
}