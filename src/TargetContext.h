#pragma once 

#include "Dir.h"

#include <SFML/Graphics.hpp>

// information required by IGhostTargeter to computer where ghost should go
namespace Pacman
{
    class TargetContext
    {
        public: 
            sf::Vector2i pacman_tile;
            Dir pacman_dir;
            sf::Vector2i blinky_tile;
            bool scatter_mode; 
    };
}