#pragma once

#include "IPathingStrategy.h"

namespace Pacman
{
    class GreedyManhattanPathingStrategy : public IPathingStrategy
    {
        public:
            Dir chooseNext(const Maze& maze, PathQuery& query) const override;
    };
}