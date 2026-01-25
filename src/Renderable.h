#pragma once

#include "AnimationLibrary.h"
#include "MoveableEntity.h"
#include "IAnimationResolver.h"

#include <SFML/Graphics.hpp>

namespace Pacman
{
    class Renderable
    {
        public:
            Renderable(IAnimationResolver* animationResolver,
                        const MoveableEntity* entity);
            IAnimationResolver* animationResolver_;
            const MoveableEntity& entity_;

            void update(sf::Time dt);
            void draw(sf::RenderTarget& window);
    };
}