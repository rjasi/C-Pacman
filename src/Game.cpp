#include "Game.h"
#include "Logger.h"

#include <iostream>
#include <vector> 

namespace Pacman
{
    Game::Game()
    : window_(sf::VideoMode({800, 600}), "Pacman"), 
    menu_(window_.getSize()) 
    {
        state_ = GameState::MainMenu;
        loadAllAssets();
        gameView_ = std::make_unique<GameView>(textureCache_);
        window_.setFramerateLimit(60);
    }

    void Game::run()
    {
        sf::Clock clock;
        const sf::Time STEP = sf::milliseconds(8); // fixed simulation step
        sf::Time accumulator = sf::Time::Zero;
        while (window_.isOpen()) 
        {
            processEvents();

            sf::Time frameTime = clock.restart();
            if (frameTime > sf::milliseconds(250))
            {
                frameTime = sf::milliseconds(250);
            }

            accumulator += frameTime;

            // Run simulation at fixed rate
            while (accumulator >= STEP)
            {
                update(STEP);
                accumulator -= STEP;
            }


            render();   
        }
    }


    void Game::processEvents() 
    {
        while (const std::optional<sf::Event> event = window_.pollEvent())
        {
            // exit
            if (event->is<sf::Event::Closed>())
            {
                window_.close();
            }

            if (state_ == GameState::MainMenu) 
            {
                menu_.handleEvent(*event);
            } 
            else if (state_ == GameState::Playing) 
            {
                gameView_->handleEvent(*event);   
            }
        }
    }

    void Game::update(sf::Time dt) 
    {
        if (state_ == GameState::MainMenu) 
        {
            auto action = menu_.consumeAction();
            if (action == MenuAction::StartGame) 
            {
                Logger::instance().info("Menu: StartGame");
                startNewGame();
                state_ = GameState::Playing;
            } 
            else if (action == MenuAction::Quit) 
            {
                Logger::instance().info("Menu: Quit");
                window_.close();
            }
        } 
        else if (state_ == GameState::Playing) 
        {
            gameView_->update(dt);
            // gameplay update later
        }
    }

    void Game::render() 
    {
        window_.clear();

        if (state_ == GameState::MainMenu) 
        {
            menu_.render(window_);
        } 
        else if (state_ == GameState::Playing) 
        {
            gameView_->render(window_);
        }

        window_.display();
    }

    void Game::startNewGame()
    {
        gameView_->reset();
    }

    void Game::loadAllAssets()
    {
        textureCache_.load("atlas",  "assets/atlas.png",  false);
        textureCache_.load("maze",   "assets/maze.png",   false);
        textureCache_.load("pellet", "assets/pellet.png", false);
        textureCache_.load("power_pellet", "assets/power_pellet.png", false);
    }


}