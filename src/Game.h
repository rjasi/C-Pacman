#pragma once

#include "AnimationLibrary.h"
#include "MainMenu.h"
#include "GameState.h"
#include "GameView.h"
#include "TextureCache.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

namespace Pacman
{
    class Game 
    {
        private: 
            sf::RenderWindow window_;
            GameState state_ = GameState::MainMenu;
            MainMenu menu_;

            // unique ptr for delayed construction
            std::unique_ptr<GameView> gameView_;
            std::unique_ptr<AnimationLibrary> animationLibrary_;

            TextureCache textureCache_;
            
            void processEvents();
            void update(sf::Time dt);
            void render();
            void startNewGame();
            void loadAllAssets();

        public: 
            Game();
            void run();        
    };
}