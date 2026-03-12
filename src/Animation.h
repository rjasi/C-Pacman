#pragma once

#include "AtlasRegion.h"
#include "MoveableEntity.h"

#include <SFML/Graphics.hpp>


namespace Pacman
{
    // this SHOULD NOT be shared between different entites because sf::Sprite and timing data is specific to a single 
    // instance
    // each entity that needs animations needs its own instance of Animation() i.e game actor and Cutsceneactor
    // given a list of frames determine which to draw
    class Animation
    {
        public: 
            Animation() = delete; // due to sf::Sprite not having a default constructor, this can't either
            Animation(sf::Texture& texture,
                const Atlas::AtlasRegion& region,
                int frameCountRow, // how many frames on same row as region
                sf::Time frameTime,
                sf::Vector2f origin = {8.0f, 8.0f}, // all character sprites are 16x16 so center them at 8,8
                int row = 0,
                const std::vector<sf::IntRect>& additionalFrames = {},// specifically for pacman as for left, down, up sprites are not inline with final closed frame on 488,0
                bool loop = true); 

            Animation(const Animation& other);
            void setRow(int row);
            void setFrameCount(int n);
            void update(sf::Time dt);
            void reset();
            sf::Sprite& sprite();
            void setLoop(bool loop);
            
        private:
            void apply();

            sf::Sprite sprite_;
            Atlas::AtlasRegion region_{};
            int frameCount_ = 0;
            int row_ = 0;

            int current_ = 0;
            bool loop_ = true;
            sf::Time elapsed_ = sf::Time::Zero;
            sf::Time frameTime_ = sf::milliseconds(100);
            std::vector<sf::IntRect> frameRects_;


    };
}