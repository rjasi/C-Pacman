#include "GameView.h"

#include <iostream>
namespace Pacman
{
    GameView::GameView(TextureCache& textCache)
    : mazeSprite_(textCache.get("maze")),
    pacManSprite_(textCache.get("atlas")),
    pelletSprite_(textCache.get("pellet")),
    powerPelletSprite_(textCache.get("power_pellet"))
    {
        // TODO maybe move this to an AssetManager class
        if (!maze_.loadFromFile("assets/level1.txt"))
        {
            std::cerr << "ERROR LOADING";
        }

        mazeSprite_.setTexture(textCache.get("maze"));

        auto& t = textCache.get("maze");
        auto s = t.getSize();
        std::cerr << "maze texture: " << s.x << "x" << s.y << "\n";


        pacManSprite_.setPosition(maze_.tileToWorld(1,1));
        pacmanEntity_.setPosition(maze_.tileToWorld(1,1));
        pelletSprite_.setOrigin({4.f, 4.f});
        powerPelletSprite_.setOrigin({4.f, 4.f});

        pacManSprite_.setOrigin({8.f,8.f});
        mazeSprite_.setPosition(maze_.origin());

        // pacman is 16x16, center is 8,8
        pacAnim_ = Animation(pacManSprite_, Atlas::PacmanRight, 3, sf::milliseconds(60));

        assetsLoaded_ = true;
    }

    void GameView::reset() 
    {
        if (!assetsLoaded_) 
        {
            throw std::runtime_error("GameView::reset() called before loadAssets()");
        }

        // view takes in center of image, then size hence * 0.5 
        worldView_ = sf::View({400.f, 300.f}, {800.f, 600.f});

        mazeSprite_.setPosition(maze_.origin());
    }

    void GameView::render(sf::RenderTarget& window) 
    {
        window.setView(worldView_);
        window.draw(mazeSprite_);

        drawPellets(window);
        // don't animate pacman if not moving 
        if(pacmanEntity_.direction() != Dir::None)
        {
            pacManSprite_.setRotation(pacmanEntity_.rotation());
        }
        pacManSprite_.setPosition(pacmanEntity_.position());
        window.draw(pacManSprite_);
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
        else
        {
            pacAnim_.reset();
        }
    }

    void GameView::drawPellets(sf::RenderTarget& window)
    {
        for (int row = 0; row < maze_.rowCount(); row++)
        {
            for (int col = 0; col < maze_.colCount(); col++)
            {
                if (maze_.isPellet(row, col))
                {
                    pelletSprite_.setPosition(maze_.tileToWorld(row, col));
                    window.draw(pelletSprite_);
                }
                else if (maze_.isPowerPellet(row, col))
                {
                    powerPelletSprite_.setPosition(maze_.tileToWorld(row, col));
                    window.draw(powerPelletSprite_);
                }
            }
        }
    }
}

