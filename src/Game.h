#pragma once

#include "AnimationLibrary.h"
#include "MainMenu.h"
#include "GameState.h"
#include "GameView.h"
#include "TextureCache.h"
#include "TileFontLibrary.h"
#include "ScorePopupRenderer.h"

#include <string_view>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

namespace Pacman
{
    class Game 
    {
        private:
            static constexpr int FRAMERATE_LIMIT = 240;
            static constexpr std::string_view ICON_PATH = "assets/icon.png";
            sf::RenderWindow window_;
            GameState state_ = GameState::Playing;
            MainMenu menu_;

            // unique ptr for delayed construction
            std::unique_ptr<GameView> gameView_;
            std::unique_ptr<AnimationLibrary> animationLibrary_;
            std::unique_ptr<TileFontLibrary> tileFontLibrary_;
            std::unique_ptr<ScorePopupRenderer> scorePopupRenderer_;
            GameAudio gameAudio_;

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