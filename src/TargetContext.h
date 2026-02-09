#pragma once 

#include "Dir.h"
#include "TileRC.h"

#include <SFML/Graphics.hpp>

// information required by IGhostTargeter to computer where ghost should go
namespace Pacman
{
    class TargetContext
    {
        public: 
            TileRC pacman_tile;
            Dir pacman_dir;
            TileRC blinky_tile;
            bool scatter_mode; 
    };
}