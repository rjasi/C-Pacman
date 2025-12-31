#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstddef>

namespace Pacman::Ui
{
    enum class Anchor 
    {
        TopLeft, TopCenter, TopRight,
        CenterLeft, Center, CenterRight,
        BottomLeft, BottomCenter, BottomRight
    };

    // Convert an anchor into an absolute pixel position inside a window
    inline sf::Vector2f anchorPos(Anchor a, const sf::Vector2u& win) 
    {
        const float w = static_cast<float>(win.x);
        const float h = static_cast<float>(win.y);

        switch (a) 
        {
            case Anchor::TopLeft:      return {0.f,   0.f};
            case Anchor::TopCenter:    return {w/2.f, 0.f};
            case Anchor::TopRight:     return {w,     0.f};

            case Anchor::CenterLeft:   return {0.f,   h/2.f};
            case Anchor::Center:       return {w/2.f, h/2.f};
            case Anchor::CenterRight:  return {w,     h/2.f};

            case Anchor::BottomLeft:   return {0.f,   h};
            case Anchor::BottomCenter: return {w/2.f, h};
            case Anchor::BottomRight:  return {w,     h};
        }
        return {w/2.f, h/2.f};
    }

    // Percent of window size, like CSS (% of width/height)
    // Example: percent(win, 0.5f, 0.2f) => (50% width, 20% height)
    inline sf::Vector2f percent(const sf::Vector2u& win, float x, float y) 
    {
        return 
        {
            x * static_cast<float>(win.x),
            y * static_cast<float>(win.y)
        };
    }

    // Convert em units to pixels based on a text's character size
    inline float em(const sf::Text& text, float units) 
    {
        return units * static_cast<float>(text.getCharacterSize());
    }

    // origin is top left corner in SFML, make it so it is the center
    // localbounds is not always 0,0 so add to whatever it currently is
    inline void setOriginToCenter(sf::Transformable& t, const sf::FloatRect& localBounds) {
        t.setOrigin({
            localBounds.position.x + localBounds.size.x * 0.5f,
            localBounds.position.y + localBounds.size.y * 0.5f
        });
    }

    inline void centerOrigin(sf::Text& text) 
    {
        setOriginToCenter(text, text.getLocalBounds());
    }

    inline void centerOrigin(sf::Sprite& sprite) 
    {
        setOriginToCenter(sprite, sprite.getLocalBounds());
    }

    inline void centerOrigin(sf::Shape& shape) 
    {
        setOriginToCenter(shape, shape.getLocalBounds());
    }

    // Place a text at an anchor, with an additional pixel offset
    inline void place(sf::Text& text, const sf::Vector2u& win, Anchor a, sf::Vector2f offsetPx = {0.f, 0.f}) 
    {
        centerOrigin(text);
        text.setPosition(anchorPos(a, win) + offsetPx);
    }

    // Place a text at a percent position, with optional pixel offset
    inline void place(sf::Text& text, const sf::Vector2u& win, sf::Vector2f percentPos, sf::Vector2f offsetPx = {0.f, 0.f}) 
    {
        centerOrigin(text);
        text.setPosition(percent(win, percentPos.x, percentPos.y) + offsetPx);
    }



    // Layout a vertical column of texts centered as a block.
    // blockAnchor: where the whole column is anchored (e.g., Center)
    // spacingPx: distance between rows in pixels
    // extraOffsetPx: shift the whole block (use % or em)
    inline void layoutColumn(std::vector<sf::Text>& items, const sf::Vector2u& win,
        Anchor blockAnchor = Anchor::Center, float spacingPx = 40.f,
        sf::Vector2f extraOffsetPx = {0.f, 0.f}) 
    {
        if (items.empty())
            return;

        // Center origins first so bounds behave as expected
        for (auto& t : items) 
        {
            centerOrigin(t);
        }

        const float totalHeight = spacingPx * static_cast<float>(items.size() - 1);
        const sf::Vector2f base = anchorPos(blockAnchor, win) + extraOffsetPx;

        const float startY = base.y - totalHeight * 0.5f;

        for (std::size_t i = 0; i < items.size(); ++i) 
        {
            items[i].setPosition({ base.x, startY + static_cast<float>(i) * spacingPx });
        }
    }


    // same as layoutColumn but rows are left aligned with largest item
    // centeres the largest item then left aligns other items to it
    inline void layoutLeftAlignedColumn(
        std::vector<sf::Text>& items,
        const sf::Vector2u& window,
        float spacingPx)
    {

        // all rows will take the left x of the largest item
        float maxWidth = 0.f;
        for (const sf::Text& t : items) 
        {
            maxWidth = std::max(maxWidth, t.getLocalBounds().size.x);
        }
        // center of window - half width of widest item
        const float leftX = window.x * 0.5f - maxWidth * 0.5f;


        const float totalHeight = spacingPx * (items.size() - 1);
        const float startY = window.y * 0.5f - totalHeight * 0.5f;

        for (std::size_t i = 0; i < items.size(); ++i) 
        {
            sf::Text& text = items[i];
            const sf::FloatRect bounds = text.getLocalBounds();

            // origin is top left by default
            text.setOrigin({
                bounds.position.x,
                bounds.position.y + bounds.size.y * 0.5f
            });

            text.setPosition({ leftX, startY + i * spacingPx });
        }
    }

}