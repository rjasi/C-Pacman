#include "GameView.h"

#include <iostream>
namespace Pacman
{
    GameView::GameView(TextureCache& textCache, AnimationLibrary* animationLibrary, TileFontLibrary* tileFontLibrary, 
        ScorePopupRenderer* scorePopupRenderer, GameAudio& gameAudio)
    : 
    gameAudio_(gameAudio),
    textCache_(textCache),
    mazeSprite_(textCache_.get("maze")),
    pelletSprite_(textCache_.get("pellet")),
    animationLibrary_(animationLibrary),
    powerPelletSprite_(textCache_.get("power_pellet")),
    pacmanLivesSprite_(textCache_.get("atlas"), Pacman::Atlas::PacmanLives.IntRect()),
    tileFontLibrary_(tileFontLibrary),
    scorePopupRenderer_(scorePopupRenderer),
    world_(gameAudio_)
    {
        pelletSprite_.setOrigin({4.f, 4.f});
        powerPelletSprite_.setOrigin({4.f, 4.f});
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
        
        mazeSprite_.setPosition(world_.maze().origin());
    }

    void GameView::render(sf::RenderTarget& window) 
    {
        worldView_.setSize(ScreenConfig::VirtualScreen);
        worldView_.setCenter(ScreenConfig::VirtualScreen / 2.f);
        worldView_.setViewport(
            ScreenConfig::letterboxViewport(window.getSize(), 
            ScreenConfig::VirtualScreen));
        mazeSprite_.setPosition(ScreenConfig::MazeOrigin);
        window.setView(worldView_);


        if (world_.activeCutscene() != Cutscenes::None)
        {
            drawCutscene(window);
            return;
        }

        // else draw normal game world


        window.draw(mazeSprite_);

        drawPellets(window);
    
        for (auto& renderable : renderables_)
        {
            renderable.draw(window);
        }
        
        for (const TextPopup& popup : world_.textPopups())
        {
            drawPopup(window, popup);
        }

        for (const ScorePopup& popup : world_.scorePopups())
        {
            drawPopup(window, popup);
        }

        drawUi(window);

        drawPopup(window, {{0.f, 80.f}, sf::seconds(100), TextColors::YELLOW, "\"Blinkly\"! "});
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
        uiLayout_.update(dt);

        if (world_.requestedCutscene() != Cutscenes::None)
        {
            switch (world_.requestedCutscene())
            {
                case Cutscenes::Intermission1:
                    CutsceneLibrary::Intermission1(cutscenePlayer_, textCache_.get("atlas"), gameAudio_);
                    cutscenePlayer_.start();
                    world_.notifyCutsceneStarted();
                    break;
                default:
                    break;
            }
        }
        if (cutscenePlayer_.finished())
        {
            cutscenePlayer_.reset();
            world_.notifyCutsceneFinished();
        }

        if (cutscenePlayer_.active())
        {
            cutscenePlayer_.update(dt);
        }


        if (world_.state() == WorldState::Playing)
        {
            animationLibrary_->update(dt);
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

    void GameView::drawPopup(sf::RenderTarget& window, const TextPopup& popup)
    {
            const TileFont& textRenderer = tileFontLibrary_->get(popup.color);
            textRenderer.render(window, popup);
    }
    
    void GameView::drawPopup(sf::RenderTarget& window, const ScorePopup& popup)
    {
        scorePopupRenderer_->render(window, popup);
    }

    void GameView::drawUi(sf::RenderTarget& window)
    {
        const TileFont& textRenderer = tileFontLibrary_->get(TextColors::WHITE);
        if (uiLayout_.oneUpVisible())
        {
            textRenderer.render(window, TextColors::WHITE, std::string(UiLayout::OneUpText), UiLayout::OneUpLabel);
        }
        textRenderer.render(window, TextColors::WHITE, UiLayout::intToStringScore(world_.score()), UiLayout::ScoreValue);

        //lives
        for (int i = 0; i < std::min(world_.lives(), UiLayout::MaxLivesDisplayed); i++)
        {
            sf::Vector2f livesPos =  UiLayout::LivesPosition + sf::Vector2f{UiLayout::LivesSpacing * i, 0};
            pacmanLivesSprite_.setPosition(livesPos);
            window.draw(pacmanLivesSprite_);
        }
    }

    void GameView::drawCutscene(sf::RenderTarget& window)
    {
        cutscenePlayer_.render(window);
    }
}

