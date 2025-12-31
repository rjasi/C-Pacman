#include "Level.h"

#include <iostream>
#include <fstream>

namespace Pacman
{
    bool Level::loadFromFile(const std::string& path)
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
            // Ignore empty lines (optional, but helpful)
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
        const std::size_t expectedWidth = tempGrid.front().size();
        for (const auto& row : tempGrid) 
        {
            if (row.size() != expectedWidth) 
            {
                std::cerr << "Inconsistent row width in level file: " << path << '\n';
                return false;
            }
        }

        // Only commit if everything is valid
        tiles = std::move(tempGrid);
        return true;
    }

    const std::vector<std::string>&Level::getTiles() const
    {
        return tiles;
    }
}