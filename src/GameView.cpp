#include "GameView.h"

namespace Pacman
{

    GameView::GameView()
    {
        if (!mapTexture_.loadFromFile("assets/maze.png")) 
        {
            throw std::runtime_error("Failed to load map PNG");
        }


        // for pixel art: avoid blur when scaling
        mapTexture_.setSmooth(false);
        mapSprite_.emplace(mapTexture_);
        mapSprite_->setPosition({0.f, 0.f});

        assetsLoaded_ = true;
    }

    void GameView::reset() 
    {
        if (!assetsLoaded_) 
        {
            throw std::runtime_error("GameView::reset() called before loadAssets()");
        }

        sf::Vector2u sz = mapTexture_.getSize();

        auto size = sf::Vector2f(
            static_cast<float>(sz.x),  static_cast<float>(sz.y));

        // view takes in center of image, then size hence * 0.5 
        worldView_ = sf::View({400.f, 300.f}, {800.f, 600.f});

        mapSprite_->setPosition({0.f, 0.f});
    }

    void GameView::render(sf::RenderTarget& window) 
    {
        window.setView(worldView_);
        window.draw(*mapSprite_);
    }

    void GameView::handleEvent(const sf::Event& event)
    {

    }
}

