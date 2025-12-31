#pragma once
#include <SFML/Graphics.hpp>
// #include <SFML/Rect.hpp>

namespace Pacman::TextUtilities 
{
    void CenterText(sf::Text& text, const sf::Vector2u& windowSize);

    sf::Vector2f PercentOffset(float xPercent, float yPercent,
                           const sf::Vector2u& windowSize);
}