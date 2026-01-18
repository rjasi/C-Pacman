#pragma once

#include "AnimationLibrary.h"
#include "MoveableEntity.h"

#include <SFML/Graphics.hpp>

namespace Pacman
{
    class Renderable
    {
        public:
            Renderable(DirectionalAnimation* animationClips,
                        const MoveableEntity* entity);
            DirectionalAnimation* animationClips_;
            const MoveableEntity* entity_;

            void update(sf::Time dt);
            void draw(sf::RenderTarget& window);
    };
}