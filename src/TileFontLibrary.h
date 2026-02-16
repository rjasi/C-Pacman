#pragma once 

#include "AtlasRegion.h"
#include "TextureCache.h"
#include "TileFont.h"
#include "TextColors.h"

#include <string_view>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace Pacman
{
    class TileFontLibrary
    {
        private:
            const sf::Texture* atlas_ = nullptr;
            std::unordered_map<TextColors, TileFont> tileFonts_;

        public:
            // in text.png each color has 4 rows in the 8x8 grid
            static constexpr int COLOR_BLOCK_HEIGHT = 4;
            static constexpr std::string_view ALL_CHARS = "ABCEDEFGHIJKLMNOPQRZTUVWXYZ0123456789";

            TileFontLibrary(TextureCache& cache)
            : atlas_(&cache.get("text"))
            {

            }

            // const TileFont& operator[](TextColors color)
            // {
            //     return tileFonts_[static_cast<size_t>(color)];
            // }

            TileFont& get(TextColors color)
            {
                return tileFonts_[color];
            }

            // TileFont& operator[](TextColors c) {
            //     return fonts_[static_cast<size_t>(c)];
            // }
            
            void load()
            {
                int colorIndex = 0;
                for (TextColors color : AllTextColors)
                {
                    std::array<sf::IntRect, NUM_CHARACTERS> rects{};
                    std::array<bool, NUM_CHARACTERS> has{};

                    int colorRowStart = colorIndex * COLOR_BLOCK_HEIGHT;
                    for (char c : ALL_CHARS)
                    {
                        if (c >= 'A' && c <= 'O')
                        {
                            Atlas::AtlasRegion region{{colorRowStart, 0},{TEXT_TILE_H, TEXT_TILE_W}};

                            unsigned char offset = c - 'A'; 

                            rects[(unsigned char) c] =  Atlas::frameRect(region, offset, colorRowStart);
                            has[(unsigned char) c] = true;

                            auto p = rects[(unsigned char) c];
                            // std::cerr << "FOUND\n" << p.position.x << " " << p.position.y << " " << (unsigned int)offset << "\n";

                        }
                    }
                    TileFont tile{rects, has, atlas_};
                    tileFonts_[color] = tile;
                }
            }

    };

}