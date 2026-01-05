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

        tiles_ = std::move(tempGrid);
        height_ = colCount;
        width_ = rowCount;
        return true;
    }

    const std::vector<std::string>& Maze::getTiles() const
    {
        return tiles_;
    }

    bool Maze::isWall(int r, int c) const
    {
        if (r > width_ || c > height_)
        {
            return false;
        }

        return tiles_[r][c] == WALL;
    }

    bool Maze::isPellet(int r, int c) const
    {
        if (r > width_ || c > height_)
        {
            return false;
        }

        return tiles_[r][c] == PELLET;
    }

    // std::string& Maze::operator[](std::size_t row) 
    // {
    //     return tiles_[row];
    // }

    const std::string& Maze::operator[](std::size_t row) const 
    {
        return tiles_[row];
    }

    int Maze::rowCount()
    {
        return height_;
    }

    int Maze::colCount()
    {
        return width_;
    }

    sf::Vector2f Maze::origin() const 
    { 
        return origin_; 
    }

    // where in the tile grid is current entity in based on its screen coordinates
    sf::Vector2i Maze::worldToTile(sf::Vector2f world) const
    {
        // transformed Coordinates, subtract position on screen to 0,0
        sf::Vector2f transformed = world - origin_;
        return { (int)std::floor(transformed.x / TILE_SIZE), (int)std::floor(transformed.y / TILE_SIZE) };
    }

    // center of current sprite's tile 
    // take in int row and col position, add .5 for center then mult by tile size    sf::Vector2f Maze::tileCenter(sf::Vector2i t) const
    sf::Vector2f Maze::tileCenter(sf::Vector2i t) const
    {
        return 
        { 
            origin_.x + (t.x + 0.5f) * TILE_SIZE, 
            origin_.y + (t.y + 0.5f) * TILE_SIZE 
        };
    }

    // use to snap to grid when sprite is close enough to the center of a tile
    bool Maze::nearTileCenter(sf::Vector2f p) const 
    {
        sf::Vector2i t = worldToTile(p);
        sf::Vector2f c = tileCenter(t);
        return (std::abs(p.x - c.x) <= CENTER_EPS) &&
            (std::abs(p.y - c.y) <= CENTER_EPS);
    }

    // relative to maze origin
    sf::Vector2f Maze::getTileCoordinates(int row, int col)
    {
        return 
        {
            origin_.x + col*TILE_SIZE + TILE_SIZE/2, 
            origin_.y + row*TILE_SIZE+ TILE_SIZE/2// 0 indexed, + TILE_SIZE/2
        };
    }



   
}