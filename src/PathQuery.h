#pragma once

#include "Dir.h"

#include <SFML/Graphics.hpp>

namespace Pacman
{
    class PathQuery
    {
        public:
            sf::Vector2i current_tile;
            Dir current_direction;
            sf::Vector2i target_tile;
            bool canReverse = false; 
    };
}