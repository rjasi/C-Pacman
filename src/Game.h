#pragma once

#include "Level.h"
#include "MainMenu.h"
#include "GameState.h"
#include "GameView.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

namespace Pacman
{
    class Game 
    {
        private: 
            Level level_; 
            int score_; 
            int lives_;
            sf::RenderWindow window_;
            GameState state_ = GameState::MainMenu;
            MainMenu menu_;
            GameView game_;
            
            void processEvents();
            void update(float dt);
            void render();
            void startNewGame();

        public: 
            Game();

            void run();
            void printLevel() const;
        
    };
}