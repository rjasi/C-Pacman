#include "GreedyManhattanPathingStrategy.h"
#include "PathUtils.h"
#include "Random.h"

#include <limits>
#include <cmath>
#include <vector>
#include <random>


namespace Pacman
{
    Dir GreedyManhattanPathingStrategy::chooseNext(const Maze& maze, PathQuery& query) const
    {
        std::vector<Dir> bestDirs;
        bestDirs.reserve(4);

        int bestScore = std::numeric_limits<int>::max();

        // order of dir in list matters as original game priority was Up, Left, Down, Right
        for (Dir d : {Dir::Up, Dir::Left, Dir::Down, Dir::Right})
        {
            if (!query.canReverse && d == DirUtils::opposite(query.current_direction))
            {
                continue;
            }

            if (d == Dir::Up && !maze.canTurnUpAtTile(query.current_tile, query.enforceForbiddenTileTurns))
            {
                continue;
            }

            TileRC nextStep = PathUtils::step(d, query.current_tile);
            if (maze.isWall(nextStep) && !maze.isInWarpTunnel(nextStep))
            {
                continue;
            }

            int score = PathUtils::manhattanDistance(query.target_tile, nextStep);
            if (score < bestScore)
            {
                bestDirs.clear(); 
                bestDirs.push_back(d); 
                bestScore = score;
            }
            else if (score == bestScore)
            {
                bestDirs.push_back(d); 
            }
        }

        if(bestDirs.size() <= 0)
        {
            // should not happen with maze design there is always at least 1 valid
            // non reversing direction at any intersection, but todo research on this
            query.canReverse = true;
            return chooseNext(maze, query);
        }

        if (query.deterministicTiebreaker)
        {
            return bestDirs.front();
        }
        return bestDirs[randomInt(0, bestDirs.size() - 1)]; // size - 1 because rand function is inclusive
    }
}