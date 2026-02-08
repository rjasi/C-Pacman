#include "GreedyManhattanPathingStrategy.h"
#include "PathUtils.h"

#include <limits>
#include <cmath>
#include <vector>
#include <random>


namespace Pacman
{
    //todo move this to an RNG class
    int randomInt(int min, int max)
    {
        static std::random_device rd;              // non-deterministic seed
        static std::mt19937 gen(rd());              // Mersenne Twister engine
        std::uniform_int_distribution<int> dist(min, max);

        return dist(gen);
    }
    
    Dir GreedyManhattanPathingStrategy::chooseNext(const Maze& maze, PathQuery& query) const
    {
        std::vector<Dir> bestDirs;
        bestDirs.reserve(4);

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
            //should not happen, but todo research on this
            query.canReverse = true;
            return chooseNext(maze, query);
        }

        return bestDirs[randomInt(0, bestDirs.size() - 1)]; // size - 1 because rand function is inclusive
    }
}