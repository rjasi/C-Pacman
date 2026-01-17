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
            Animation() = delete; // due to sf::Sprite not having a default constructor, this can't either
            Animation(sf::Texture& texture,
                const Atlas::AtlasRegion& region,
                int frameCount,
                sf::Time frameTime,
                sf::Vector2f origin = {8.0f, 8.0f}, // all character sprites are 16x16 so center them at 8,8
                int row = 0);

            void setRow(int row);
            void setFrameCount(int n);
            void update(sf::Time dt);
            void reset();
            sf::Sprite& sprite();
            
        private:
            void apply();

            sf::Sprite sprite_;
            Atlas::AtlasRegion region_{};
            int frameCount_ = 0;
            int row_ = 0;

            int current_ = 0;
            sf::Time elapsed_ = sf::Time::Zero;
            sf::Time frameTime_ = sf::milliseconds(100);


    };
}