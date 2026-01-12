#include "Maze.h"

#include <iostream>
#include <fstream>

namespace Pacman
{
    Maze::Maze()
    {
        // TODO maybe move this to an AssetManager class
        if (!loadFromFile("assets/level1.txt"))
        {
            std::cerr << "ERROR LOADING";
        }
    }


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
        colCount_ = colCount;
        rowCount_ = rowCount;
        return true;
    }

    const std::vector<std::string>& Maze::getTiles() const
    {
        return tiles_;
    }

    bool Maze::isWall(int r, int c) const
    {
        if (r > rowCount_ || c > colCount_)
        {
            return false;
        }

        return tiles_[r][c] == WALL;
    }

    bool Maze::isPellet(int r, int c) const
    {
        if (r > rowCount_  || c > colCount_)
        {
            return false;
        }

        return tiles_[r][c] == PELLET;
    }

    bool Maze::isPowerPellet(int r, int c) const
    {
        if (r > rowCount_  || c > colCount_)
        {
            return false;
        }

        return tiles_[r][c] == POWER_PELLET;
    }

    const std::string& Maze::operator[](std::size_t row) const 
    {
        return tiles_[row];
    }

    int Maze::rowCount() const
    {
        return rowCount_;
    }

    int Maze::colCount() const
    {
        return colCount_;
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

    // from row, col on the maze, get screen coordinates
    sf::Vector2f Maze::tileToWorld(int row, int col) const
    {
        return 
        {
            origin_.x + col*TILE_SIZE + TILE_SIZE/2, 
            origin_.y + row*TILE_SIZE+ TILE_SIZE/2// 0 indexed, + TILE_SIZE/2
        };
    }  

    bool Maze::tryEatPellet(int row, int col)
    {
        if(!isInBounds(row, col))
        {
            return false;;
        }

        if(tiles_[row][col] == PELLET)
        {
            tiles_[row][col] = EMPTY; 
            return true;
        }

        return false;
    }

    bool Maze::tryEatPowerPellet(int row, int col)
    {
        if(!isInBounds(row, col))
        {
            return false;;
        }

        if(tiles_[row][col] == POWER_PELLET)
        {
            tiles_[row][col] = EMPTY; 
            return true;
        }

        return false;
    }

    bool Maze::isInBounds(int r, int c) const
    {
        return r >= 0 && c >= 0 &&
            r < rowCount_ && c < colCount_;
    }

    // bool Maze::isTile(int r, int c, char value) const
    // {
    //     return inBounds(r, c) && tiles_[r][c] == value;
    // }

    // bool Maze::isWall(int r, int c) const        { return isTile(r, c, WALL); }
    // bool Maze::isPellet(int r, int c) const      { return isTile(r, c, PELLET); }
    // bool Maze::isPowerPellet(int r, int c) const { return isTile(r, c, POWER_PELLET); }
}