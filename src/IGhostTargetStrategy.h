#pragma once 

#include "TargetContext.h"
#include "TileRC.h"

#include <SFML/Graphics.hpp>

//given info about where things are in the maze determine where to go for ghosts (not pathfinding)
namespace Pacman
{
    class IGhostTargetStrategy
    {
        public:
            virtual ~IGhostTargetStrategy() = default;
            virtual TileRC getTarget(const TargetContext& ctx) const = 0;
            virtual TileRC scatterTarget(const TargetContext& ctx) const = 0;
    };
}