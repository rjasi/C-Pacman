
#pragma once 

#include "Dir.h"

#include <SFML/Graphics.hpp>

namespace Pacman
{
    class PathUtils
    {
        public:
            static int manhattanDistance(sf::Vector2i a, sf::Vector2i b)
            {
                return abs(a.x - b.x) + abs(a.y - b.y);
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

            static sf::Vector2i step(Dir dir, sf::Vector2i tile)
            {
                switch (dir)
                {
                    case Dir::Up:
                        return {tile.x, tile.y - 1};
                    case Dir::Down:
                        return {tile.x, tile.y + 1};
                    case Dir::Left:
                        return {tile.x - 1, tile.y};
                    case Dir::Right: 
                        return {tile.x + 1, tile.y};
                    default:
                        return tile;
                }
            }
    };
}