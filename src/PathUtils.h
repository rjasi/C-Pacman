
#pragma once 

#include "Dir.h"
#include "TileRC.h"

#include <SFML/Graphics.hpp>

namespace Pacman
{
    class PathUtils
    {
        public:
            static int manhattanDistance(TileRC& a, TileRC& b)
            {
                return abs(a.r - b.r) + abs(a.c - b.c);
            }

            static Dir opposite(Dir d) 
            {
                switch (d) 
                {
                    case Dir::Up: 
                        return Dir::Down;
                    case Dir::Down: 
                        return Dir::Up;
                    case Dir::Left: 
                        return Dir::Right;
                    case Dir::Right: 
                        return Dir::Left;
                    default: 
                        return Dir::None;
                }
            }

            static TileRC step(Dir dir, TileRC& tile)
            {
                switch (dir)
                {
                    case Dir::Up:
                        return {tile.r - 1, tile.c};
                    case Dir::Down:
                        return {tile.r + 1, tile.c};
                    case Dir::Left:
                        return {tile.r, tile.c - 1};
                    case Dir::Right: 
                        return {tile.r, tile.c + 1};
                    default:
                        return tile;
                }
            }
    };
}