#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

namespace Pacman
{
    // Maze.h has a 2d array that stores the maze. rows = y coordinate, cols = x coordinate
    class TileRC
    {
        public:
            int r = 0; // y in pixel world
            int c = 0; // x in pixel world

            TileRC() = default; 

            explicit TileRC(const sf::Vector2i& v)
            {
                std::cerr << "here2\n";
                r = v.y;
                c = v.x;
            }

            explicit TileRC(sf::Vector2i& v)
            {
                std::cerr << "here1\n";
                r = v.y;
                c = v.x;
            }

            constexpr TileRC(const TileRC& tile)
            : r(tile.r), c(tile.c)
            {
     
            }

            // TileRC(const TileRC&& tile)
            // : r(tile.r), c(tile.c)
            // {
     
            // }

            constexpr TileRC(int row, int col)
            : r(row), c(col)
            {

            }

            TileRC operator+(const TileRC& a)
            {
                return {a.r + r, a.c + c};
            }
    };

}