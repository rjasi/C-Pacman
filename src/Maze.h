#pragma once

#include "TileRC.h"
#include "Dir.h"
#include "PathUtils.h"

#include <vector>
#include <SFML/Graphics.hpp>

namespace Pacman
{
    class Maze 
    {
        private: 
            int rowCount_;
            int colCount_;
            sf::Vector2f origin_{ 0, 0 }; // pixel location on screen

        public:
            std::vector<std::string> tiles_;

            static constexpr int TILE_SIZE = 8; // pixel size in world
            static constexpr float CENTER_EPS = 0.40f; // remove
            static constexpr int WARP_TILE_ROW = 14;
            static constexpr char WALL = '#';
            static constexpr char PELLET = '.';
            static constexpr char POWER_PELLET = 'o';
            static constexpr char EMPTY = ' ';
            
            // todo update to TileRC
            static constexpr TileRC INFRONT_DOOR = {11, 13};
            static constexpr TileRC HOUSE_CENTER = {14, 13};
            static constexpr TileRC HOUSE_LEFT = {14, 11};
            static constexpr TileRC HOUSE_RIGHT = {14, 15};


            Maze();
            Maze(const Maze& maze) = delete;

            bool isInBounds(TileRC& tile) const;
            bool shouldWarp(TileRC& tile) const;
            void applyWarp(sf::Vector2f& pos) const;

            bool isInWarpTunnel(TileRC& tile) const;

            bool isWall(TileRC& tile) const;
            bool isPellet(TileRC& tile) const;
            bool isPowerPellet(TileRC& tile) const;
            bool tryEatPellet(const sf::Vector2f& worldPos);
            bool tryEatPowerPellet(const sf::Vector2f& worldPos);

            bool loadFromFile(const std::string& location);

            const std::vector<std::string>& getTiles() const;

            const std::string& operator[](std::size_t row) const;

            int rowCount() const;
            int colCount() const;

            sf::Vector2f origin() const;

            TileRC worldToTile(sf::Vector2f world) const;
            sf::Vector2f tileToWorld(const TileRC& t) const;
            sf::Vector2f tileToWorld(const sf::Vector2i& loc) const;
            sf::Vector2f tileToWorldOnBoundary(const TileRC& tile) const;
            sf::Vector2f tileToWorldOnBoundary(sf::Vector2i loc) const;
            sf::Vector2f tileCenterClampX(sf::Vector2i t) const;

            // check if next tile from current position and direction can be entered
            bool canEnterNextTile(Dir d, const sf::Vector2f& pos) const;
            bool canEnterNextTile(Dir d, const TileRC& tile) const;


            sf::Vector2f tileCenter(TileRC t) const;
            sf::Vector2f tileCenter(const sf::Vector2f& worldPos) const;

            bool nearTileCenter(sf::Vector2f p, const float eps) const;

            bool nearTileCenterX(sf::Vector2f p, const float eps) const;
            bool nearTileCenterY(sf::Vector2f p, const float eps) const;

    };
}