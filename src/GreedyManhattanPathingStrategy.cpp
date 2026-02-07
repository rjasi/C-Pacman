#include "GreedyManhattanPathingStrategy.h"
#include "PathUtils.h"

#include <limits>
#include <cmath>

namespace Pacman
{
    Dir GreedyManhattanPathingStrategy::chooseNext(const Maze& maze, const PathQuery& query) const
    {
        Dir best = Dir::None;
        int bestScore = std::numeric_limits<int>::max();

        // loop through valid dirs and pick the best
        for (Dir d : {Dir::Up, Dir::Down, Dir::Left, Dir::Right})
        {
            if (!query.canReverse && d == PathUtils::opposite(query.current_direction))
            {
                continue;
            }

            sf::Vector2i nextStep = PathUtils::step(d, query.current_tile);
            if (maze.isWall(nextStep.y, nextStep.x))
            {
                continue;
            }

            int score = PathUtils::manhattanDistance(query.target_tile, nextStep);
            if (score < bestScore)
            {
                best = d; 
                bestScore = score;
            }
        }

        if (best == Dir::None)
        {
            // not possible, in the grid there is always a valid move without reversing
        }

        return best;
    }
}