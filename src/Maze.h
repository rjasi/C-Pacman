#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

namespace Pacman
{
    class Maze 
    {
        private: 
            int rowCount_;
            int colCount_;
            sf::Vector2f origin_{ 320.f, 320.f }; // pixel location on screen

        public:
            std::vector<std::string> tiles_;

            static constexpr int TILE_SIZE = 8;
            static constexpr float CENTER_EPS = 0.40f;
            static constexpr char WALL = '#';
            static constexpr char PELLET = '.';
            static constexpr char POWER_PELLET = 'o';
            static constexpr char EMPTY = ' ';
            
            static constexpr sf::Vector2i INFRONT_DOOR = {11, 13};
            static constexpr sf::Vector2i HOUSE_CENTER = {14, 13};
            static constexpr sf::Vector2i HOUSE_LEFT = {14, 11};
            static constexpr sf::Vector2i HOUSE_RIGHT = {14, 15};


            Maze();

            bool isInBounds(int r, int c) const;
            bool isWall(int r, int c) const;
            bool isPellet(int r, int c) const;
            bool isPowerPellet(int r, int c) const;
            bool tryEatPellet(int r, int c);
            bool tryEatPowerPellet(int r, int c);

            bool loadFromFile(const std::string& location);

            const std::vector<std::string>& getTiles() const;

            const std::string& operator[](std::size_t row) const;

            int rowCount() const;
            int colCount() const;

            sf::Vector2f origin() const;

            sf::Vector2i worldToTile(sf::Vector2f world) const;
            sf::Vector2f tileToWorld(int row, int col) const;
            sf::Vector2f tileToWorld(const sf::Vector2i& loc) const;
            sf::Vector2f tileToWorldOnBoundary(int row, int col) const;
            sf::Vector2f tileToWorldOnBoundary(sf::Vector2i loc) const;
            sf::Vector2f tileCenterClampX(sf::Vector2i t) const;


            sf::Vector2f tileCenter(sf::Vector2i t) const;
            bool nearTileCenter(sf::Vector2f p, const float eps) const;
    };
}