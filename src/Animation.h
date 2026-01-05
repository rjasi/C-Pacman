#pragma once

#include "AtlasRegion.h"
#include "MoveableEntity.h"

#include <SFML/Graphics.hpp>


namespace Pacman
{
    // given a list of frames determine which to draw
    class Animation
    {
        public: 
            Animation() = default;
            Animation(sf::Sprite& sprite,
                const Atlas::AtlasRegion& region,
                int frameCount,
                sf::Time frameTime,
                int row = 0);

            void setRow(int row);
            void setFrameCount(int n);
            void update(sf::Time dt);
            void reset();
            
        private:
            void apply();

            sf::Sprite* sprite_;
            Atlas::AtlasRegion region_{};
            int frameCount_ = 0;
            int row_ = 0;

            int current_ = 0;
            sf::Time elapsed_ = sf::Time::Zero;
            sf::Time frameTime_ = sf::milliseconds(100);


    };
}