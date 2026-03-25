#pragma once 

#include "TextColors.h"
#include "Popup.h"

#include <array>
#include <algorithm>
#include <iostream>
#include <string>
#include <cctype>

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

            std::string toUpper(std::string s) const
            {
                std::transform(s.begin(), s.end(), s.begin(),
                            [](unsigned char c) { return std::toupper(c); });
                return s;
            }

            void render(sf::RenderTarget& window, const TextPopup& popup, bool center = true) const
            {
                sf::Vector2f currentPos = popup.pos;
                int index = 0;

                std::string upper = toUpper(popup.text);

                for (char c: upper)
                {
                    if (c == ' ')
                    {
                        currentPos.x  += TEXT_TILE_W;
                        continue;
                    }

                    if (hasSprite(c))
                    {
                        auto sprite = getTextSprite(c);
                        sprite.setPosition({std::round(currentPos.x), std::round(currentPos.y)});
                        if (center)
                        {
                            sprite.setOrigin({TEXT_TILE_W/2, TEXT_TILE_H/2}); // center origin
                        }
                        else
                        {
                            sprite.setOrigin({0, 0}); // top left is sfml default
                        }
                        window.draw(sprite);
                        
                        if (c == '(')
                        {
                            currentPos.x  += TEXT_TILE_W * 6;
                        }
                        else if (c == ')')
                        {
                            currentPos.x  += TEXT_TILE_W * 2;
                        }
                        else 
                        {
                            currentPos.x  += TEXT_TILE_W;
                        }


                        // std::cerr << "drawn\n";
                    }
                    else 
                    {
                        // std::cerr << "no sprite\n";
                    }
                }
             

            }

            // todo maybe refactor Popup since not every text is a popup
            void render(sf::RenderTarget& window, const std::string& text, const sf::Vector2f& pos, bool center = false) const
            {
                // color is a placeholder.. not used
                render(window, {pos, sf::Time::Zero, TextColors::RED, text}, false);
            }

    };
}
