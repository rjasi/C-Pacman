#pragma once
#include <SFML/Graphics.hpp>

namespace Pacman
{
    class ScreenConfig
    {
        public:
            static constexpr sf::Vector2f VirtualScreen{224.f, 288.f};
            static constexpr sf::Vector2f MazeSize{224.f, 248.f};
            static constexpr float TopUI = 24.f;
            static constexpr sf::Vector2f MazeOrigin{0.f, TopUI};

            static sf::FloatRect letterboxViewport(sf::Vector2u win, 
                                                    sf::Vector2f virt)
            {
                float wr = float(win.x) / float(win.y);
                float vr = virt.x / virt.y;

                float w = 1.f, h = 1.f, x = 0.f, y = 0.f;

                if (wr > vr) 
                {
                    w = vr / wr;
                    x = (1.f - w) * 0.5f;
                } 
                else 
                {
                    h = wr / vr;
                    y = (1.f - h) * 0.5f;
                }

                return {{x, y}, {w, h}};
            }
    };
    
}