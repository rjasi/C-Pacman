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
            {r.origin.x + frameIndex * r.frameSize.x, r.origin.y + row        * r.frameSize.y },
            { r.frameSize.x, r.frameSize.y }
        );
    } 

    //constants
    static constexpr AtlasRegion PacmanRight 
    {
        {455, 0},   // origin
        {16, 16}    // frame size
    };


}