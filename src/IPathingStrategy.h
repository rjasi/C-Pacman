#pragma once 

#include "PathQuery.h"
#include "Maze.h"

// how to actually get to a tile based on some heuristic

namespace Pacman
{
    class IPathingStrategy
    {
        public: 
            virtual ~IPathingStrategy() = default;
            virtual Dir chooseNext(const Maze& maze, PathQuery& query) const = 0;
    };
}
