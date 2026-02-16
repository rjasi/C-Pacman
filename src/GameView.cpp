#include "GameView.h"

#include <iostream>
namespace Pacman
{
    GameView::GameView(TextureCache& textCache, AnimationLibrary* animationLibrary, TileFontLibrary* tileFontLibrary)
    : mazeSprite_(textCache.get("maze")),
    pelletSprite_(textCache.get("pellet")),
    animationLibrary_(animationLibrary),
    powerPelletSprite_(textCache.get("power_pellet")),
    tileFontLibrary_(tileFontLibrary)
    {
        pelletSprite_.setOrigin({4.f, 4.f});
        powerPelletSprite_.setOrigin({4.f, 4.f});
        mazeSprite_.setPosition(world_.maze().origin());
        assetsLoaded_ = true;

        renderables_.emplace_back(animationLibrary_->ghostResolvers_[GameCharactersIndex::BLINKY].get(), &world_.blinky());
        renderables_.emplace_back(animationLibrary_->ghostResolvers_[GameCharactersIndex::PINKY].get(), &world_.pinky());
        renderables_.emplace_back(animationLibrary_->ghostResolvers_[GameCharactersIndex::INKY].get(), &world_.inky());
        renderables_.emplace_back(animationLibrary_->ghostResolvers_[GameCharactersIndex::CLYDE].get(), &world_.clyde());
        renderables_.emplace_back(animationLibrary_->pacmanResolver_.get(), &world_.pacman());
    }

    void GameView::reset() 
    {
        if (!assetsLoaded_) 
        {
            throw std::runtime_error("GameView::reset() called before loadAssets()");
        }

        // view takes in center of image, then size hence * 0.5 
        // worldView_ = sf::View({400.f, 300.f}, {800.f, 600.f});
        worldView_.setSize({224.f, 248.f});
        worldView_.setCenter({224.f/2, 248.f/2});

        // worldView_.zoom(0.8f);  
        // worldView_.move({-260.f, -160.f});
        mazeSprite_.setPosition(world_.maze().origin());
    }

    void GameView::render(sf::RenderTarget& window) 
    {
        window.setView(worldView_);
        window.draw(mazeSprite_);

        drawPellets(window);
        // don't animate pacman if not moving 
        if (world_.pacman().direction() != Dir::None)
        {
            animationLibrary_->pacmanRight_.sprite().setRotation(world_.pacman().rotation());
        }
    
        for (auto& renderable : renderables_)
        {
            renderable.draw(window);
        }
        
        for (const Popup& popup : world_.popups())
        {
            TileFont& textRenderer = tileFontLibrary_->get(popup.color);
            textRenderer.render(window, popup);
        }

    }

    void GameView::handleEvent(const sf::Event& event)
    {
        if (auto* key = event.getIf<sf::Event::KeyPressed>()) 
        {
            switch (key->scancode) 
            {
                case sf::Keyboard::Scancode::Up:
                    world_.setPlayerRequestedDir(Dir::Up);
                    break;
                case sf::Keyboard::Scancode::Down:
                    world_.setPlayerRequestedDir(Dir::Down);
                    break;
                case sf::Keyboard::Scancode::Left:
                    world_.setPlayerRequestedDir(Dir::Left);
                    break;
                case sf::Keyboard::Scancode::Right:
                    world_.setPlayerRequestedDir(Dir::Right);
                    break;
                default:
                    break;
            }
        }
    }

    void GameView::update(sf::Time dt)
    {
        world_.update(dt);

        if (world_.state() == WorldState::Playing)
        {
            animationLibrary_->update(dt);
            // original pacman game seems to have mouth open when stopped
            if(world_.pacman().direction() != Dir::None)
            {
                animationLibrary_->pacmanRight_.update(dt);
            }
            else
            {
                animationLibrary_->pacmanRight_.reset();
            }

        }


        
    }

    void GameView::drawPellets(sf::RenderTarget& window)
    {
        const Maze& maze = world_.maze();

        for (int row = 0; row < maze.rowCount(); row++)
        {
            for (int col = 0; col < maze.colCount(); col++)
            {
                TileRC tile{row, col};
                if (maze.isPellet(tile))
                {
                    pelletSprite_.setPosition(maze.tileToWorld(tile));
                    window.draw(pelletSprite_);
                }
                else if (maze.isPowerPellet(tile) && world_.powerPelletVisible())
                {
                    powerPelletSprite_.setPosition(maze.tileToWorld(tile));
                    window.draw(powerPelletSprite_);
                }
            }
        }
    }
}

