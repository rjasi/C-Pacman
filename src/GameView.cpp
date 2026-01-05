#include "GameView.h"

#include <iostream>
namespace Pacman
{
    GameView::GameView()
    {
        if (!mapTexture_.loadFromFile("assets/maze.png")) 
        {
            throw std::runtime_error("Failed to load map PNG");
        }

        if(!spriteAtlasTexture_.loadFromFile("assets/all_sprites.png"))
        {
            throw std::runtime_error("Failed to load map PNG");
        }

        if(!pelletTexture_.loadFromFile("assets/pellet.png"))
        {
            throw std::runtime_error("Failed to load pellet PNG");
        }

        if (!maze_.loadFromFile("assets/level1.txt"))
        {
            std::cerr << "ERROR LOADING";
        }

        // for pixel art: avoid blur when scaling
        mapTexture_.setSmooth(false);
        spriteAtlasTexture_.setSmooth(false);
        pelletTexture_.setSmooth(false);

        mapSprite_.emplace(mapTexture_);
        mapSprite_->setPosition(maze_.origin());
        pacManSprite_.emplace(spriteAtlasTexture_);
        // pacManSprite_->setScale({2.f, 2.f}); // integer scale for crispness


        // pacManSprite_->setPosition({1*8 + 4, 1*8+ 4}); // 0 indexed, + 4 for center
        pacManSprite_->setPosition(maze_.getTileCoordinates(1,1));
        // pacmanEntity_.setPosition({1*8 + 4, 1*8+ 4});
        pacmanEntity_.setPosition(maze_.getTileCoordinates(1,1));

        pacManSprite_->setOrigin({8.f,8.f});// pacman is 16x16, center is 8,8
        pacAnim_ = Animation(*pacManSprite_, Atlas::PacmanRight, 3, sf::milliseconds(80));

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

        mapSprite_->setPosition(maze_.origin());
    }

    void GameView::render(sf::RenderTarget& window) 
    {
        window.setView(worldView_);
        window.draw(*mapSprite_);

        // drawPellets(window);
        // don't animate pacman if not moving 
        if(pacmanEntity_.direction() != Dir::None)
        {
            pacManSprite_->setPosition(pacmanEntity_.position());
            pacManSprite_->setRotation(pacmanEntity_.rotation());
        }

        window.draw(*pacManSprite_);
    }

    void GameView::handleEvent(const sf::Event& event)
    {
        if (auto* key = event.getIf<sf::Event::KeyPressed>()) 
        {
            switch (key->scancode) 
            {
                case sf::Keyboard::Scancode::Up:
                    pacmanEntity_.requestDirection(Dir::Up);
                    break;
                case sf::Keyboard::Scancode::Down:
                    pacmanEntity_.requestDirection(Dir::Down);
                    break;
                case sf::Keyboard::Scancode::Left:
                    pacmanEntity_.requestDirection(Dir::Left);
                    break;
                case sf::Keyboard::Scancode::Right:
                    pacmanEntity_.requestDirection(Dir::Right);
                    break;
                default:
                    break;
            }
        }
    }

    void GameView::update(sf::Time dt)
    {
        pacmanEntity_.update(dt, maze_);
        if(pacmanEntity_.direction() != Dir::None)
        {
            pacAnim_.update(dt);
        }

    }

    void GameView::drawPellets(sf::RenderTarget& window)
    {
        for (int row = 0; row < maze_.rowCount(); row++)
        {
            for (int col = 0; col < maze_.colCount(); col++)
            {
                if(maze_.isPellet(row, col))
                {
                    
                }
            }
        }
    }
}

