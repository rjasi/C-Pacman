#pragma once

#include "GameState.h"

#include "TextureCache.h"
#include "TileFontLibrary.h"

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>


namespace Pacman
{
    enum class MenuAction 
    {
        None,
        StartGame,
        HighScore,
        Quit
    };

    // not main menu not used other than just to start game
    class MainMenu
    {
        public:
           explicit MainMenu(const sf::Vector2u& windowSize);

            void handleEvent(const sf::Event& event);

            void update(float dt) {}

            void render(sf::RenderTarget& target) const;

            // Game reads this; if Start/Quit was selected, it returns that once
            MenuAction consumeAction();

        private:
            void rebuildText();
            void updateHighlight();


            sf::Font font_;
            sf::Text title_;
            std::vector<sf::Text> items_;

            std::vector<std::string> labels_ = {"Start", "High scores", "Quit"};
            int selected_ = 0;

            MenuAction pendingAction_ = MenuAction::StartGame;

            sf::Vector2u windowSize_;
    };


}