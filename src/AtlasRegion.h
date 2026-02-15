#pragma once 

#include <SFML/Graphics.hpp>

namespace Pacman::Atlas
{
    class AtlasRegion
    {
        public:
            sf::Vector2i origin;
            sf::Vector2i frameSize;
    };

    // returns region of sprite sheet of a single frame relative to origin
    // use with sprite to specify a which area to display
    inline sf::IntRect frameRect(const AtlasRegion& r, int frameIndex, int row = 0)
    {
        return sf::IntRect(
            {r.origin.x + frameIndex * r.frameSize.x, r.origin.y + row * r.frameSize.y },
            { r.frameSize.x, r.frameSize.y }
        );
    } 

    //constants
    inline constexpr AtlasRegion PacmanRight 
    {
        {456, 0},   // origin
        {16, 16}    // frame size
    };

    inline constexpr AtlasRegion BlinkyRight 
    {
        {456, 64},
        {16, 16}
    };

    inline constexpr AtlasRegion BlinkyLeft
    {
        {488, 64},
        {16, 16}
    };

    inline constexpr AtlasRegion BlinkyUp
    {
        {520, 64},
        {16, 16}
    };

    inline constexpr AtlasRegion BlinkyDown
    {
        {552, 64},
        {16, 16}
    };

    //pinky
    inline constexpr AtlasRegion PinkyRight 
    {
        {456, 80},
        {16, 16}
    };

    inline constexpr AtlasRegion PinkyLeft
    {
        {488, 80},
        {16, 16}
    };

    inline constexpr AtlasRegion PinkyUp
    {
        {520, 80},
        {16, 16}
    };

    inline constexpr AtlasRegion PinkyDown
    {
        {552, 80},
        {16, 16}
    };

    // inky

    inline constexpr AtlasRegion InkyRight 
    {
        {456, 96},
        {16, 16}
    };

    inline constexpr AtlasRegion InkyLeft
    {
        {488, 96},
        {16, 16}
    };

    inline constexpr AtlasRegion InkyUp
    {
        {520, 96},
        {16, 16}
    };

    inline constexpr AtlasRegion InkyDown
    {
        {552, 96},
        {16, 16}
    };

    // clyde
    inline constexpr AtlasRegion ClydeRight 
    {
        {456, 112},
        {16, 16}
    };

    inline constexpr AtlasRegion ClydeLeft
    {
        {488, 112},
        {16, 16}
    };

    inline constexpr AtlasRegion ClydeUp
    {
        {520, 112},
        {16, 16}
    };

    inline constexpr AtlasRegion ClydeDown
    {
        {552, 112},
        {16, 16}
    };

    inline constexpr AtlasRegion FrightenedGhost
    {
        {584, 64},
        {16, 16}
    };

    inline constexpr AtlasRegion FrightenedGhostFlash
    {
        {616, 64},
        {16, 16}
    };

}