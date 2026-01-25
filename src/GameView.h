#pragma once

#include "AnimationLibrary.h"
#include "Renderable.h"
#include "GhostEnum.h"
#include "TextureCache.h"
#include "World.h"

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <string>
#include <vector>

namespace Pacman
{
    class GameView 
    {
        public:
            GameView() = delete;
            explicit GameView(TextureCache& cache, AnimationLibrary* animationLibrary);
            void reset();
            void update(sf::Time dt);
            void render(sf::RenderTarget& window);
            void handleEvent(const sf::Event& event);

        private:
            sf::View worldView_;
            sf::Sprite mazeSprite_;
            sf::Sprite pelletSprite_;
            sf::Sprite powerPelletSprite_;

            std::vector<Renderable> renderables_;

            World world_;
            AnimationLibrary* animationLibrary_;

            bool assetsLoaded_ = false;

            void loadAssets();
            void drawPellets(sf::RenderTarget& window);
    };
}