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
            std::vector<std::string> tiles_;

        public:
            static constexpr int TILE_SIZE = 8;
            static constexpr float CENTER_EPS = 0.40f;
            static constexpr char WALL = '#';
            static constexpr char PELLET = '.';
            static constexpr char POWER_PELLET = 'o';

            bool isWall(int r, int c) const;
            bool isPellet(int r, int c) const;
            bool isPowerPellet(int r, int c) const;

            bool loadFromFile(const std::string& location);

            const std::vector<std::string>& getTiles() const;

            const std::string& operator[](std::size_t row) const;

            int rowCount();
            int colCount();

            sf::Vector2f origin() const;

            sf::Vector2i worldToTile(sf::Vector2f world) const;
            sf::Vector2f tileToWorld(int row, int col) const;

            sf::Vector2f tileCenter(sf::Vector2i t) const;
            bool nearTileCenter(sf::Vector2f p) const;
    };
}