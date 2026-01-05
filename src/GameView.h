#pragma once

#include "Maze.h"
#include "Animation.h"
#include "MoveableEntity.h"

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <string>

namespace Pacman
{
    class GameView 
    {
        public:
            GameView();
            void reset();
            void update(sf::Time dt);
            void render(sf::RenderTarget& window);
            void handleEvent(const sf::Event& event);
            static constexpr int TILE_SIZE = 8;

        private:
            sf::View worldView_;
            sf::Texture mapTexture_;
            sf::Texture spriteAtlasTexture_;
            sf::Texture pelletTexture_;
            std::optional<sf::Sprite> mapSprite_;
            std::optional<sf::Sprite> pacManSprite_;
            std::optional<sf::Sprite> pelletSprite_;
            Maze maze_;
            Animation pacAnim_;
            MoveableEntity pacmanEntity_;

            bool assetsLoaded_ = false;

            void loadAssets();
            void drawPellets(sf::RenderTarget& window);
            sf::Vector2f getTileCoordinates(int row, int col);
    };
}