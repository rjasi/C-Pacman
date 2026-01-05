#pragma once

#include "Maze.h"
#include "Animation.h"
#include "MoveableEntity.h"
#include "TextureCache.h"

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <string>

namespace Pacman
{
    class GameView 
    {
        public:
            GameView() = delete;
            explicit GameView(TextureCache& cache);
            void reset();
            void update(sf::Time dt);
            void render(sf::RenderTarget& window);
            void handleEvent(const sf::Event& event);
            static constexpr int TILE_SIZE = 8;

        private:
            sf::View worldView_;
            sf::Sprite mazeSprite_;
            sf::Sprite pacManSprite_;
            sf::Sprite pelletSprite_;
            sf::Sprite powerPelletSprite_;

            Maze maze_;
            Animation pacAnim_;
            MoveableEntity pacmanEntity_;

            bool assetsLoaded_ = false;

            void loadAssets();
            void drawPellets(sf::RenderTarget& window);
            sf::Vector2f getTileCoordinates(int row, int col);
    };
}