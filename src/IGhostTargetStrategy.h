#pragma once 

#include "TargetContext.h"
#include "TileRC.h"
#include "Dir.h"

#include <SFML/Graphics.hpp>

//given info about where things are in the maze determine where to go for ghosts (not pathfinding)
namespace Pacman
{
    class IGhostTargetStrategy
    {
        public:
            virtual ~IGhostTargetStrategy() = default;
            virtual TileRC getTarget(const TargetContext& ctx) const = 0;
            // scatter target does not require TargetContext but leave it in for now 
            // if in the future TargetContext is incorporated
            virtual TileRC scatterTarget(const TargetContext& ctx) const = 0;
    };
}