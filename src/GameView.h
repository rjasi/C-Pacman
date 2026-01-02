#pragma once
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
            void update(float /*dt*/) {}
            void render(sf::RenderTarget& window);
            void handleEvent(const sf::Event& event);

        private:
            sf::View worldView_;

            sf::Texture mapTexture_;
            std::optional<sf::Sprite> mapSprite_;

            bool assetsLoaded_ = false;

            void loadAssets();

    };
}