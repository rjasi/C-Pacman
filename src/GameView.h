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

        private:
            sf::View worldView_;
            sf::Texture mapTexture_;
            sf::Texture spriteAtlasTexture_;
            std::optional<sf::Sprite> mapSprite_;
            std::optional<sf::Sprite> pacManSprite_;

            Maze maze_;
            Animation pacAnim_;
            MoveableEntity pacmanEntity_;

            bool assetsLoaded_ = false;

            void loadAssets();
    };
}