#pragma once

#include "TextColors.h"

#include <string>
#include <variant>

#include <SFML/Graphics.hpp>

namespace Pacman
{
    class Popup
    {
        public:
            sf::Vector2f pos;
            sf::Time durationRemaining;
            virtual ~Popup() = default;

            Popup
            (
                sf::Vector2f pos, 
                sf::Time durationRemaining
            )
            : pos(pos), 
            durationRemaining(durationRemaining)
            {

            }
    };

    class TextPopup : public Popup
    {
        public:
            TextPopup
            (
                sf::Vector2f pos,
                sf::Time durationRemaining,
                TextColors color,
                std::string text)
            : Popup(pos, durationRemaining), 
            color(color),
            text(text)
            {

            }
            std::string text;
            TextColors color;

    };

    enum class Scores
    {
        BlueScore200,
        BlueScore400,
        BlueScore800,
        BlueScore1600,
        PinkScore100,
        PinkScore300,
        PinkScore500,
        PinkScore700,
        PinkScore1000,
        PinkScore2000,
        PinkScore3000,
        PinkScore5000,
    };

    class ScorePopup : public Popup
    {
        public:
            ScorePopup
            ( 
                sf::Vector2f pos,
                sf::Time durationRemaining,
                Scores score
            ) : Popup(pos, durationRemaining), 
            score(score)
            {

            }

            Scores score;
    };

    // using Popup = std::variant<TextPopup, ScorePopup>;
}