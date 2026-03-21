#pragma once 

#include <SFML/Graphics.hpp>

#include "GhostEnum.h"

namespace Pacman::Atlas
{
    class AtlasRegion
    {
        public:
            sf::Vector2i origin;
            sf::Vector2i frameSize;
            sf::IntRect IntRect() const
            {
                return {origin, frameSize};
            }
    };

    // returns region of sprite sheet of a single frame relative to origin
    // use with sprite to specify a which area to display
    inline sf::IntRect frameRect(const AtlasRegion& r, int frameIndex = 0, int row = 0)
    {
        // IntRect is {{left (x), top (y)}, {width, height}}
        return sf::IntRect(
            {r.origin.x + frameIndex * r.frameSize.x, r.origin.y + row * r.frameSize.y },
            { r.frameSize.x, r.frameSize.y }
        );
    } 

    //constants
    inline constexpr AtlasRegion Blank 
    {
        {600, 16},   // origin
        {16, 16}    // frame size
    };

    inline constexpr AtlasRegion PacmanRight 
    {
        {456, 0},   // origin
        {16, 16}    // frame size
    };

    inline constexpr AtlasRegion PacmanLeft
    {
        {456, 16},
        {16, 16}
    };
    
    inline constexpr AtlasRegion PacmanUp
    {
        {456, 32},
        {16, 16}    
    };
    
    inline constexpr AtlasRegion PacmanDown 
    {
        {456, 48},
        {16, 16}    
    };

    inline constexpr AtlasRegion PacmanLastFrame 
    {
        {488, 0},
        {16, 16}    
    };

    inline constexpr AtlasRegion PacmanDying
    {
        {504, 0},
        {16, 16}    
    };

    inline constexpr AtlasRegion PacmanLives
    {
        {584, 16},   // origin
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

    inline constexpr AtlasRegion BlueScore200
    {
        {456, 128},
        {16, 16}
    };

    inline constexpr AtlasRegion BlueScore400
    {
        {472, 128},
        {16, 16}
    };

    inline constexpr AtlasRegion BlueScore800
    {
        {488, 128},
        {16, 16}
    };

    inline constexpr AtlasRegion BlueScore1600
    {
        {504, 128},
        {16, 16}
    };

    inline constexpr AtlasRegion PinkScore100
    {
        {456, 144},
        {16, 16}
    };

    inline constexpr AtlasRegion PinkScore300
    {
        {472, 144},
        {16, 16}
    };

    inline constexpr AtlasRegion PinkScore500
    {
        {488, 144},
        {16, 16}
    };

    inline constexpr AtlasRegion PinkScore700
    {
        {504, 144},
        {16, 16}
    };

    inline constexpr AtlasRegion PinkScore1000
    {
        {520, 144},
        {24, 16}
    };

    inline constexpr AtlasRegion PinkScore2000
    {
        {512, 160},
        {32, 16}
    };

    inline constexpr AtlasRegion PinkScore3000
    {
        {512, 176},
        {32, 16}
    };

    inline constexpr AtlasRegion PinkScore5000
    {
        {512, 192},
        {32, 16}
    };




    inline constexpr AtlasRegion GhostEyesRight
    {
        {584, 80},
        {16, 16}
    };

    inline constexpr AtlasRegion GhostEyesLeft
    {
        {600, 80},
        {16, 16}
    };

    inline constexpr AtlasRegion GhostEyesUp
    {
        {616, 80},
        {16, 16}
    };

    inline constexpr AtlasRegion GhostEyesDown
    {
        {632, 80},
        {16, 16}
    };

    // fruits

    inline constexpr AtlasRegion Cherry
    {
        {488, 48},
        {16, 16}
    };

    inline constexpr AtlasRegion Strawberry
    {
        {504, 48},
        {16, 16}
    };

    inline constexpr AtlasRegion Peach
    {
        {520, 48},
        {16, 16}
    };

    inline constexpr AtlasRegion Apple
    {
        {536, 48},
        {16, 16}
    };

    inline constexpr AtlasRegion Grapes
    {
        {552, 48},
        {16, 16}
    };

    inline constexpr AtlasRegion Galaxian
    {
        {568, 48},
        {16, 16}
    };

    inline constexpr AtlasRegion Bell
    {
        {584, 48},
        {16, 16}
    };

    inline constexpr AtlasRegion Key
    {
        {600, 48},
        {16, 16}
    };



    class DirRegions
    {
        public: 
            const Atlas::AtlasRegion& right;
            const Atlas::AtlasRegion& left;
            const Atlas::AtlasRegion& up;
            const Atlas::AtlasRegion& down;
            
    };


    inline constexpr DirRegions NormalRegionsFor(GameCharacters id)
    {
        switch (id)
        {
            case GameCharacters::Blinky: return { Atlas::BlinkyRight, Atlas::BlinkyLeft, Atlas::BlinkyUp, Atlas::BlinkyDown };
            case GameCharacters::Pinky:  return { Atlas::PinkyRight,  Atlas::PinkyLeft,  Atlas::PinkyUp,  Atlas::PinkyDown  };
            case GameCharacters::Inky:   return { Atlas::InkyRight,   Atlas::InkyLeft,   Atlas::InkyUp,   Atlas::InkyDown   };
            case GameCharacters::Clyde:  return { Atlas::ClydeRight,  Atlas::ClydeLeft,  Atlas::ClydeUp,  Atlas::ClydeDown  };
            case GameCharacters::Pacman: return { Atlas::PacmanRight, Atlas::PacmanLeft, Atlas::PacmanUp, Atlas::PacmanDown };

            default:
                // unreachable, but keep compiler happy:
                return { Atlas::BlinkyRight, Atlas::BlinkyLeft, Atlas::BlinkyUp, Atlas::BlinkyDown };
        }
        
    }

}