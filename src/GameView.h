#pragma once

#include "Animation.h"
#include "TextureCache.h"
#include "World.h"

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

        private:
            sf::View worldView_;
            sf::Sprite mazeSprite_;
            sf::Sprite pacManSprite_;
            sf::Sprite pelletSprite_;
            sf::Sprite powerPelletSprite_;

            Animation pacAnim_;
            World world_;

            bool assetsLoaded_ = false;

            void loadAssets();
            void drawPellets(sf::RenderTarget& window);
    };
}