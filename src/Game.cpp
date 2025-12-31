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
        lives_ = 3;
        bool success = level_.loadFromFile("assets/level1.txt");
        if (!success)
        {
            std::cerr << "ERROR LOADING";
        }

        state_ = GameState::MainMenu;
        window_.setFramerateLimit(60);
    }

    void Game::printLevel() const
    {
        std::vector<std::string> tiles = level_.getTiles();
        for (const std::string& row : tiles)
        {
            std::cerr << row << "\n";
        }
    }

    void Game::run()
    {
        sf::Clock clock;

        while (window_.isOpen()) 
        {
            processEvents();

            float dt = clock.restart().asSeconds();
            update(dt);

            render();   
        }
    }


    void Game::processEvents() 
    {
        while (const std::optional<sf::Event> event = window_.pollEvent())
        {

            // Close window: exit
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
                // // gameplay input later
                // if (auto* key = event->is<sf::Event::KeyPressed>()) 
                // {
                //     if (key->scancode == sf::Keyboard::Scancode::Escape) 
                //     {
                //         // You can decide: pause menu or go back to main menu
                //         state_ = GameState::MainMenu;
                //     }
                // }
            }
        }
    }

   void Game::update(float dt) {
    (void)dt;
    if (state_ == GameState::MainMenu) {
        auto action = menu_.consumeAction();
        if (action == MenuAction::StartGame) {
            Logger::instance().info("Menu: StartGame");
            // startNewGame();
            state_ = GameState::Playing;
        } else if (action == MenuAction::Quit) {
            Logger::instance().info("Menu: Quit");
            window_.close();
        }
    } else if (state_ == GameState::Playing) {
        // gameplay update later
    }
}

void Game::render() {
    window_.clear();

    if (state_ == GameState::MainMenu) 
    {
        menu_.render(window_);
    } else if (state_ == GameState::Playing) 
    {
        // draw gameplay later (level, pacman, ghosts)
    }

    window_.display();
}

}