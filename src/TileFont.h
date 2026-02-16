#pragma once 

#include "TextColors.h"
#include "Popup.h"

#include <array>
#include <iostream>

#include <SFML/Graphics.hpp>

namespace Pacman
{
    class TileFont
    {
        private:
            const sf::Texture* atlas_ = nullptr;
            int w = 8;
            int h = 8;
            int offset = 0;// 
            std::array<sf::IntRect, NUM_CHARACTERS> rects_{};
            std::array<bool, NUM_CHARACTERS> has_{};

        public:
            TileFont() = default;
            TileFont(
                std::array<sf::IntRect, NUM_CHARACTERS> rects,
                std::array<bool, NUM_CHARACTERS> has,
                const sf::Texture* atlas )
            :
            rects_(rects),
            has_(has),
            atlas_(atlas)
            {

            }

            bool hasSprite(char c) const
            {
                unsigned char index = (unsigned char) c;
                return has_[index];
            }
        
            sf::IntRect getRect(char c) const
            {
                unsigned char index = (unsigned char) c;
                return rects_[index];
            }

            sf::Sprite getTextSprite(char c) const
            {
                auto sprite = sf::Sprite{*atlas_};
                sprite.setTextureRect(getRect(c));
                return sprite;
            }

            void render(sf::RenderTarget& window, const Popup& popup) const
            {
                sf::Vector2f currentPos = popup.pos;
                int index = 0;

                for (char c: popup.text)
                {
                    if (c == ' ')
                    {
                        currentPos.x  += TEXT_TILE_W;
                        continue;
                    }

                    if (hasSprite(c))
                    {
                        auto sprite = getTextSprite(c);
                        currentPos.x  += TEXT_TILE_W;
                        sprite.setPosition(currentPos);
                        window.draw(sprite);
                        // std::cerr << "drawn\n";
                    }
                    else 
                    {
                        // std::cerr << "no sprite\n";
                    }
                }
             

            }

    };
}
