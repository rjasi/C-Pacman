#pragma once

#include <vector>

namespace Pacman
{
    class Maze 
    {
        private: 
            int height;
            int width; 

            std::vector<std::string> tiles;

            static const int TILE_SIZE = 32;

        public:
            static constexpr char WALL = '#';

            bool isWall(int r, int c) const;

            bool loadFromFile(const std::string& location);

            const std::vector<std::string>& getTiles() const;

    };
}