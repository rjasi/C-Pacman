#pragma once

#include "Dir.h"
#include "TileRC.h"

#include <SFML/Graphics.hpp>

namespace Pacman
{
    class PathQuery
    {
        public:
            TileRC current_tile;
            Dir current_direction;
            TileRC target_tile;
            bool canReverse = false; 
    };
}