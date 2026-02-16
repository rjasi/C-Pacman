#pragma once

#include "TextColors.h"

#include <string>

#include <SFML/Graphics.hpp>

namespace Pacman
{
    class Popup
    {
        public:
            sf::Vector2f pos;
            std::string text;
            sf::Time durationRemaining;
            TextColors color;
    };
}