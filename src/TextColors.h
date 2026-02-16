#pragma once

#include <array>

namespace Pacman
{
    inline constexpr int TEXT_TILE_H = 8;
    inline constexpr int TEXT_TILE_W = 8;
    inline constexpr int NUM_CHARACTERS = 128;

    enum class TextColors
    {
        WHITE = 0,
        RED, 
        PINK,
        BLUE,
        ORANGE,
        SALMON,
        YELLOW
    };

    constexpr std::array<TextColors, 7> AllTextColors
    {
        TextColors::WHITE,
        TextColors::RED, 
        TextColors::PINK,
        TextColors::BLUE,
        TextColors::ORANGE,
        TextColors::SALMON,
        TextColors::YELLOW
    };
}