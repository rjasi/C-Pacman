#include "Maze.h"

#include <iostream>
#include <fstream>

namespace Pacman
{
    bool Maze::loadFromFile(const std::string& path)
    {
        std::ifstream file(path);
        if (!file) 
        {
            std::cerr << "Failed to open level file: " << path << '\n';
            return false;
        }

        std::vector<std::string> tempGrid;
        std::string line;

        while (std::getline(file, line)) 
        {
            if (line.empty())
                continue;

            tempGrid.push_back(line);
        }

        if (tempGrid.empty()) 
        {
            std::cerr << "Level file is empty: " << path << '\n';
            return false;
        }

        // Ensure all rows have the same width
        int rowCount = 0;
        const std::size_t colCount = tempGrid.front().size();
        for (const auto& row : tempGrid) 
        {
            if (row.size() != colCount) 
            {
                std::cerr << "Inconsistent row width in level file: " << path << '\n';
                return false;
            }
            rowCount++;
        }

        tiles = std::move(tempGrid);
        height = colCount;
        width = rowCount;
        return true;
    }

    const std::vector<std::string>& Maze::getTiles() const
    {
        return tiles;
    }

    bool Maze::isWall(int r, int c) const
    {
        if (r > width || c > height)
        {
            return false;
        }

        return tiles[r][c] == WALL;
    }
}