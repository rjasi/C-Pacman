#pragma once

#include "ScreenConfig.h"

#include <string_view>
#include <string>
#include <SFML/Graphics.hpp>

namespace Pacman
{

    class UiLayout
    {
        public: 
            static constexpr std::string_view OneUpText = "1UP";
            static constexpr sf::Vector2f OneUpLabel { 8.f * 3,  0.f };
            static constexpr sf::Vector2f ScoreValue { 8.f,  8.f };

            static constexpr std::string_view HighScoreText = "HIGH SCORE";
            static constexpr sf::Vector2f HighScoreLabel { 8.f * 9,  0.f };
            static constexpr sf::Vector2f HighScoreValue { 8.f * 10,  8.f };

            static constexpr float CenterX = ScreenConfig::VirtualScreen.x / 2.f;

            // static constexpr sf::Vector2f HighScoreLabel {CenterX, 0.f };
            // static constexpr sf::Vector2f HighScoreValue {CenterX, 8.f };

            static constexpr sf::Vector2f LivesPosition { 16.f, 272.f };
            static constexpr int MaxLivesDisplayed = 5;
            static constexpr float LivesSpacing = (float)Atlas::PacmanLives.frameSize.x;

            static constexpr sf::Vector2f FruitPosition { 208.f, 280.f };
            static constexpr float FruitSpaceing =  (float)Atlas::Cherry.frameSize.x;


            static std::string intToStringScore(int score)
            {
                std::string unpadded = std::to_string(score);
                if (score == 0) // original games shows 00 when score is 0
                {
                    unpadded += "0";
                }

                std::string padded = "";
                
                // pad a blank for each digit less than 6
                for (int i = 0; i < (6 - unpadded.size()); i++)
                {
                    padded += " ";
                }
                return padded + unpadded;
            }

            void update(sf::Time dt)
            {
                blinkElapsed1UP_ += dt;
                if (blinkElapsed1UP_ >= blinkPeriod1UP_) 
                {
                    blinkElapsed1UP_ -= blinkPeriod1UP_;
                    oneUpVisible_ = !oneUpVisible_;
                }
            }

            bool oneUpVisible() const
            {
                return oneUpVisible_;
            }

        private:
            sf::Time blinkElapsed1UP_ = sf::Time::Zero;
            sf::Time blinkPeriod1UP_  = sf::milliseconds(250); 
            bool oneUpVisible_ = true;

    };
    
}