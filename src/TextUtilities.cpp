#include "TextUtilities.hpp"

namespace Pacman::TextUtilities
{
    void CenterText(sf::Text& text, const sf::Vector2u& windowSize)
    {
        const sf::FloatRect bounds = text.getLocalBounds();

        text.setOrigin({
            bounds.position.x + bounds.size.x * 0.5f,
            bounds.position.y + bounds.size.y * 0.5f
        });

        // Place origin at the center of the window
        text.setPosition({
            windowSize.x * 0.5f,
            windowSize.y * 0.5f
        });
    }

    // to be used to position with relative % of x or y like in HTML
    sf::Vector2f PercentOffset(float xPercent, float yPercent, 
                                const sf::Vector2u& windowSize)
    {
        return {
            xPercent * windowSize.x,
            yPercent * windowSize.y
        };
    }
}