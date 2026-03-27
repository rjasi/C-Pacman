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
    mazeNoDoorBlueSprite_(textCache_.get("mazeNoDoorBlue")),
    mazeNoDoorWhiteSprite_(textCache_.get("mazeNoDoorWhite")),
    pelletSprite_(textCache_.get("pellet")),
    animationLibrary_(animationLibrary),
    powerPelletSprite_(textCache_.get("power_pellet")),
    pacmanLivesSprite_(textCache_.get("atlas"), Pacman::Atlas::PacmanLives.IntRect()),
    tileFontLibrary_(tileFontLibrary),
    scorePopupRenderer_(scorePopupRenderer),
    world_(gameAudio_),
    cherrySprite_(textCache_.get("atlas"), Pacman::Atlas::Cherry.IntRect()),
    strawberrySprite_(textCache_.get("atlas"), Pacman::Atlas::Strawberry.IntRect()),
    peachSprite_(textCache_.get("atlas"), Pacman::Atlas::Peach.IntRect()),
    appleSprite_(textCache_.get("atlas"), Pacman::Atlas::Apple.IntRect()),
    grapesSprite_(textCache_.get("atlas"), Pacman::Atlas::Grapes.IntRect()),
    galaxianSprite_(textCache_.get("atlas"), Pacman::Atlas::Galaxian.IntRect()),
    bellSprite_(textCache_.get("atlas"), Pacman::Atlas::Bell.IntRect()),
    keySprite_(textCache_.get("atlas"), Pacman::Atlas::Key.IntRect()),
    blinkyMenuSprite_(textCache_.get("atlas"), Pacman::Atlas::BlinkyRight.IntRect()),
    pinkyMenuSprite_(textCache_.get("atlas"), Pacman::Atlas::PinkyRight.IntRect()),
    inkyMenuSprite_(textCache_.get("atlas"), Pacman::Atlas::InkyRight.IntRect()),
    clydeMenuSprite_(textCache_.get("atlas"), Pacman::Atlas::ClydeRight.IntRect())
    {
        pelletSprite_.setOrigin(Atlas::Sprite8x8Origin);
        powerPelletSprite_.setOrigin(Atlas::Sprite8x8Origin);
        assetsLoaded_ = true;

        mazeSprite_.setPosition(ScreenConfig::MazeOrigin);
        mazeNoDoorBlueSprite_.setPosition(ScreenConfig::MazeOrigin);
        mazeNoDoorWhiteSprite_.setPosition(ScreenConfig::MazeOrigin);

        renderables_.emplace_back(animationLibrary_->pacmanResolver_.get(), &world_.pacman());
        renderables_.emplace_back(animationLibrary_->ghostResolvers_[GameCharactersIndex::BLINKY].get(), &world_.blinky());
        renderables_.emplace_back(animationLibrary_->ghostResolvers_[GameCharactersIndex::PINKY].get(), &world_.pinky());
        renderables_.emplace_back(animationLibrary_->ghostResolvers_[GameCharactersIndex::INKY].get(), &world_.inky());
        renderables_.emplace_back(animationLibrary_->ghostResolvers_[GameCharactersIndex::CLYDE].get(), &world_.clyde());

        cherrySprite_.setPosition(world_.fruitPos());
        cherrySprite_.setOrigin(Atlas::Sprite16x18Origin);
        strawberrySprite_.setPosition(world_.fruitPos());
        strawberrySprite_.setOrigin(Atlas::Sprite16x18Origin);
        peachSprite_.setPosition(world_.fruitPos());
        peachSprite_.setOrigin(Atlas::Sprite16x18Origin);
        appleSprite_.setPosition(world_.fruitPos());
        appleSprite_.setOrigin(Atlas::Sprite16x18Origin);
        grapesSprite_.setPosition(world_.fruitPos());
        grapesSprite_.setOrigin(Atlas::Sprite16x18Origin);
        galaxianSprite_.setPosition(world_.fruitPos());
        galaxianSprite_.setOrigin(Atlas::Sprite16x18Origin);
        bellSprite_.setPosition(world_.fruitPos());
        bellSprite_.setOrigin(Atlas::Sprite16x18Origin);
        keySprite_.setPosition(world_.fruitPos());
        keySprite_.setOrigin(Atlas::Sprite16x18Origin);
    }

    void GameView::reset() 
    {   
        world_.setStartNewGame();
    }

    void GameView::drawPlaying(sf::RenderTarget& window) 
    {
        if (world_.activeCutscene() != Cutscenes::None)
        {
            drawCutscene(window);
            drawUiFruits(window);
            return;
        }

        // else draw normal game world

        switch (world_.mazeDisplayMode())
        {
            case MazeDisplayMode::Normal:
                window.draw(mazeSprite_);
                break;
            case MazeDisplayMode::NoDoorBlue:
                window.draw(mazeNoDoorBlueSprite_);
                break;
            case MazeDisplayMode::NoDoorWhite:
                window.draw(mazeNoDoorWhiteSprite_);
                break;
            default:
                window.draw(mazeSprite_);
        }

        
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

        drawFruit(window);

        drawUi(window);
    }

    void GameView::drawIntro(sf::RenderTarget& window) 
    {

        drawUi(window);
        const TileFont& whiteTextRenderer = tileFontLibrary_->get(TextColors::WHITE);
        const Maze& maze = world_.maze();

        whiteTextRenderer.render(window, "Character / Nickname", maze.tileToWorldNonCentered({3,7}));

        if (menuTimer_ >= blinkyMenuSpriteTime_)
        {
            blinkyMenuSprite_.setPosition(maze.tileToWorldNonCentered({4,5}) + sf::Vector2f{0, 2.f});
            window.draw(blinkyMenuSprite_);
        }

        if (menuTimer_ >= blinkyCharacterTextTime_)
        {
            const TileFont& textRenderer = tileFontLibrary_->get(TextColors::RED);
            textRenderer.render(window, "-Shadow", maze.tileToWorldNonCentered({5,8}));
        }

        if (menuTimer_ >= blinkyNicknameTextTime_)
        {
            const TileFont& textRenderer = tileFontLibrary_->get(TextColors::RED);
            textRenderer.render(window, "\"Blinky\"", maze.tileToWorldNonCentered({5,19}));
        }
          
        if (menuTimer_ >= pinkyMenuSpriteTime_)
        {
            pinkyMenuSprite_.setPosition(maze.tileToWorldNonCentered({7,5}) + sf::Vector2f{0, 2.f});
            window.draw(pinkyMenuSprite_);
        }

        if (menuTimer_ >= pinkyCharacterTextTime_)
        {
            const TileFont& textRenderer = tileFontLibrary_->get(TextColors::PINK);
            textRenderer.render(window, "-Speedy", maze.tileToWorldNonCentered({8, 8}));
        }

        if (menuTimer_ >= pinkyNicknameTextTime_)
        {
            const TileFont& textRenderer = tileFontLibrary_->get(TextColors::PINK);
            textRenderer.render(window, "\"Pinky\"", maze.tileToWorldNonCentered({8,19}));
        }

        if (menuTimer_ >= inkyMenuSpriteTime_)
        {
            inkyMenuSprite_.setPosition(maze.tileToWorldNonCentered({10,5}) + sf::Vector2f{0, 2.f});
            window.draw(inkyMenuSprite_);
        }

        if (menuTimer_ >= inkyCharacterTextTime_)
        {
            const TileFont& textRenderer = tileFontLibrary_->get(TextColors::BLUE);
            textRenderer.render(window, "-Bashful", maze.tileToWorldNonCentered({11, 8}));
        }

        if (menuTimer_ >= inkyNicknameTextTime_)
        {
            const TileFont& textRenderer = tileFontLibrary_->get(TextColors::BLUE);
            textRenderer.render(window, "\"Inky\"", maze.tileToWorldNonCentered({11,19}));
        }

        if (menuTimer_ >= clydeMenuSpriteTime_)
        {
            clydeMenuSprite_.setPosition(maze.tileToWorldNonCentered({13,5}) + sf::Vector2f{0, 2.f});
            window.draw(clydeMenuSprite_);
        }

        if (menuTimer_ >= clydeCharacterTextTime_)
        {
            const TileFont& textRenderer = tileFontLibrary_->get(TextColors::ORANGE);
            textRenderer.render(window, "-Pokey", maze.tileToWorldNonCentered({14, 8}));
        }

        if (menuTimer_ >= clydeNicknameTextTime_)
        {
            const TileFont& textRenderer = tileFontLibrary_->get(TextColors::ORANGE);
            textRenderer.render(window, "\"Clyde\"", maze.tileToWorldNonCentered({14,19}));
        }

        if (menuTimer_ >= ptsSpriteTime_)
        {
            pelletSprite_.setPosition(maze.tileToWorld({21,10}));
            window.draw(pelletSprite_);
            whiteTextRenderer.render(window, "10 )", maze.tileToWorldNonCentered({21,13}));

            if (!cutscenePlayer_.active())
            {
                powerPelletSprite_.setPosition(maze.tileToWorld({23,10}) - sf::Vector2f{0, 1.f});
                window.draw(powerPelletSprite_);
            }
            whiteTextRenderer.render(window, "50 )", maze.tileToWorldNonCentered({23,13}));
        }        
        
        if (menuTimer_ >= namcoTimer_)
        {
            const TileFont& textRenderer = tileFontLibrary_->get(TextColors::PINK);
            textRenderer.render(window, "(", maze.tileToWorldNonCentered({28, 11}));
            if (!cutscenePlayer_.active())
            {
                CutsceneLibrary::IntroScreen(cutscenePlayer_, textCache_);
                cutscenePlayer_.start();
            }
            
        }

        if (cutscenePlayer_.active())
        {
            drawCutscene(window);
        }
    }

    void GameView::drawPushStart(sf::RenderTarget& window)
    {
        drawUi(window);
        const TileFont& orangeTextRenderer = tileFontLibrary_->get(TextColors::ORANGE);
        const TileFont& blueTextRenderer = tileFontLibrary_->get(TextColors::BLUE);
        const TileFont& salmonTextRenderer = tileFontLibrary_->get(TextColors::SALMON);
        const TileFont& pinkTextRenderer = tileFontLibrary_->get(TextColors::PINK);

        const Maze& maze = world_.maze();

        orangeTextRenderer.render(window, "Push enter button", maze.tileToWorldNonCentered({14, 6}));
        blueTextRenderer.render(window, "1 Player only", maze.tileToWorldNonCentered({18, 8}));
        salmonTextRenderer.render(window, "Bonus pac-man for 10000 )", maze.tileToWorldNonCentered({22, 1}));
        pinkTextRenderer.render(window, "+ ( 1980", maze.tileToWorldNonCentered({26, 8}));
    }



    void GameView::render(sf::RenderTarget& window) 
    {
        worldView_.setSize(ScreenConfig::VirtualScreen);
        worldView_.setCenter(ScreenConfig::VirtualScreen / 2.f);
        worldView_.setViewport(
            ScreenConfig::letterboxViewport(window.getSize(), 
            ScreenConfig::VirtualScreen));
        window.setView(worldView_);

        switch(screenMode_)
        {
            case ScreenMode::Intro:
                drawIntro(window);
                break;
            case ScreenMode::PushStart:
                drawPushStart(window);
                break;
            case ScreenMode::Playing:
                drawPlaying(window);
                break;
            default:
                break;
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
                case sf::Keyboard::Scancode::Space:
                    switch (screenMode_)
                    {
                        case ScreenMode::Intro:
                            menuTimer_ = sf::seconds(20.f); // speed up intro
                            break;
                        default:
                            return;
                    }
                    break;
                case sf::Keyboard::Scancode::Enter:
                    switch (screenMode_)
                    {
                        case ScreenMode::Intro:
                            gameAudio_.playSfx(SfxId::Credit);
                            cutscenePlayer_.reset();
                            screenMode_ = ScreenMode::PushStart;
                            break;
                        case ScreenMode::PushStart:
                            gameAudio_.playSfx(SfxId::Credit);
                            reset();
                            screenMode_ = ScreenMode::Playing;
                            break;
                        default:
                            return;
                    }
                    break;
                default:
                    break;
            }
        }
    }
    
    void GameView::update(sf::Time dt)
    {
        if (world_.consumeResetToIntroRequest())
        {
            screenMode_ = ScreenMode::Intro;
            menuTimer_ = sf::Time::Zero;
            cutscenePlayer_.reset();
        }

        switch(screenMode_)
        {
            case ScreenMode::Intro:
                updateIntro(dt);
                break;
            case ScreenMode::PushStart:
                break;
            case ScreenMode::Playing:
                updatePlaying(dt);
                break;
            default:
                break;
        }
    }

    void GameView::updateIntro(sf::Time dt)
    {
        menuTimer_ += dt;
        if (menuTimer_ >= namcoTimer_)
        {
            if (!cutscenePlayer_.active())
            {
                CutsceneLibrary::IntroScreen(cutscenePlayer_, textCache_);
                cutscenePlayer_.start();
            }   
        }

        if (cutscenePlayer_.active())
        {
            cutscenePlayer_.update(dt);
        }
    }

    void GameView::updatePlaying(sf::Time dt)
    {
        if (world_.requestedCutscene() != Cutscenes::None)
        {
            switch (world_.requestedCutscene())
            {
                gameAudio_.stopMusic();

                case Cutscenes::Intermission1:
                    CutsceneLibrary::Intermission1(cutscenePlayer_, textCache_.get("atlas"), gameAudio_);
                    break;
                case Cutscenes::Intermission2:
                    CutsceneLibrary::Intermission2(cutscenePlayer_, textCache_.get("atlas"), gameAudio_);                    
                    break;
                default:
                    break;
            }

            cutscenePlayer_.start();
            world_.notifyCutsceneStarted();
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

        if (world_.state() == WorldState::Playing || world_.state() == WorldState::Died)
        {
            animationLibrary_->update(dt);
        }

        world_.update(dt);
        uiLayout_.update(dt);
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
            textRenderer.render(window, std::string(UiLayout::OneUpText), UiLayout::OneUpLabel);
        }
        textRenderer.render(window, UiLayout::intToStringScore(world_.score()), UiLayout::ScoreValue);

        textRenderer.render(window, std::string(UiLayout::HighScoreText), UiLayout::HighScoreLabel);
        textRenderer.render(window, UiLayout::intToStringScore(world_.highScore()), UiLayout::HighScoreValue);

        //lives or credit depending on screen mode
        if (screenMode_ == ScreenMode::Playing)
        {
            for (int i = 0; i < std::min(world_.lives(), UiLayout::MaxLivesDisplayed); i++)
            {
                sf::Vector2f livesPos =  UiLayout::LivesPosition + sf::Vector2f{UiLayout::LivesSpacing * i, 0};
                pacmanLivesSprite_.setPosition(livesPos);
                window.draw(pacmanLivesSprite_);
            }

            drawUiFruits(window);
        }
        else 
        {
            textRenderer.render(window, "Credit  0", UiLayout::LivesPosition);
        }
        
    }

    void GameView::drawUiFruits(sf::RenderTarget& window)
    {
        int currentIndex = 0;
        for (int i = std::max(world_.level() - 6, 1); i <= world_.level(); i++, currentIndex++)
        {
            sf::Vector2f pos =  UiLayout::FruitPosition - sf::Vector2f{UiLayout::FruitSpaceing * currentIndex, 0};
            sf::Sprite& fruitSprite = getFruitSprite(world_.getFruitForLevel(i));
            fruitSprite.setPosition(pos);
            window.draw(fruitSprite);
        }  
    }

    void GameView::drawCutscene(sf::RenderTarget& window)
    {
        cutscenePlayer_.render(window);
    }

    void GameView::drawFruit(sf::RenderTarget& window)
    {
        if (world_.spawnedFruit() != Fruits::None)
        {
            sf::Sprite& fruitSprite = getFruitSprite(world_.spawnedFruit());
            fruitSprite.setPosition(world_.fruitPos());
            window.draw(fruitSprite);
        }
    }

    sf::Sprite& GameView::getFruitSprite(Fruits fruit)
    {
        switch (fruit)
        {
            case Fruits::Cherry:
                return cherrySprite_;
            case Fruits::Strawberry:
                return strawberrySprite_;
            case Fruits::Peach:
                return peachSprite_;
            case Fruits::Apple:
                return appleSprite_;
            case Fruits::Grapes:
                return grapesSprite_;
            case Fruits::Galaxian:
                return galaxianSprite_;
            case Fruits::Bell:
                return bellSprite_;
            case Fruits::Key:
                return keySprite_;
            default:
                return cherrySprite_;
        }
    }

}

