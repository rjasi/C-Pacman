
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

            static TileRC step(Dir d, const TileRC& tile)
            {
                return DirUtils::dirVecTile(d) + tile;
            }
    };
}