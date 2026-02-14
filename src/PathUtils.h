
#pragma once 

#include "Dir.h"
#include "TileRC.h"

#include <SFML/Graphics.hpp>

namespace Pacman
{
    class PathUtils
    {
        public:
            PathUtils() = delete;

            static int manhattanDistance(const TileRC& a, const TileRC& b)
            {
                return abs(a.r - b.r) + abs(a.c - b.c);
            }

            static int euclidianDistanceSquared(const TileRC& a, const TileRC& b)
            {
                int y = a.r - b.r;
                int x = a.c - b.c;
                return x * x + y * y;
            }

            static TileRC step(Dir d, const TileRC& tile)
            {
                return DirUtils::dirVecTile(d) + tile;
            }
    };
}